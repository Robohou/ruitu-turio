/**
**************************************************************************************
* @file         socket.c
* @author       WIZnet Software Team
* @version      V1.0
* @date         2015-xx-xx
* @brief        Socket�����غ���
**************************************************************************************
*/
#include "include.h"
#include "socket.h"
#include "w5500_config.h"
#include "stdio.h"

uint16_t defaultPort = 502; // ����Ĭ�϶˿�
/**
*@brief   This Socket function initialize the channel in perticular mode,
*         and set the port and wait for W5200 done it.
*@param   s: socket number.
*@param   protocol: The socket to chose.
*@param   port:The port to bind.
*@param   flag: Set some bit of MR,such as **< No Delayed Ack(TCP) flag.
*@return    1 for sucess else 0.
*/
uint8_t socket(SOCKET s, uint8_t protocol, uint16_t port, uint8_t flag)
{
   uint8_t ret;
   if (
        ((protocol&0x0F) == Sn_MR_TCP)    ||
        ((protocol&0x0F) == Sn_MR_UDP)    ||
        ((protocol&0x0F) == Sn_MR_IPRAW)  ||
        ((protocol&0x0F) == Sn_MR_MACRAW) ||
        ((protocol&0x0F) == Sn_MR_PPPOE)
      )
   {
      close(s);
      w5500_write_byte(Sn_MR(s) ,protocol | flag);
      if (port != 0) {
         w5500_write_byte( Sn_PORT0(s) ,(uint8_t)((port & 0xff00) >> 8));
         w5500_write_byte( Sn_PORT1(s) ,(uint8_t)(port & 0x00ff));
      } else {
         defaultPort++;                   /*If don't set the source port, set local_port number*/
         w5500_write_byte(Sn_PORT0(s) ,(uint8_t)((defaultPort & 0xff00) >> 8));
         w5500_write_byte(Sn_PORT1(s) ,(uint8_t)(defaultPort & 0x00ff));
      }
      w5500_write_byte( Sn_CR(s) ,Sn_CR_OPEN);      /*Run sockinit Sn_CR*/

      while( w5500_read_byte(Sn_CR(s)) )          /*Wait to process the command*/
         ;
      ret = 1;
   }
   else
   {
      ret = 0;
   }
   return ret;
}

/**
*@brief   This function close the socket and parameter is "s" which represent the socket number
*@param   s: socket number.
*@return  None
*/
void close(SOCKET s)
{
   w5500_write_byte( Sn_CR(s) ,Sn_CR_CLOSE);

   while( w5500_read_byte(Sn_CR(s) ) )            /*Wait to process the command*/
       ;
  w5500_write_byte( Sn_IR(s) , 0xFF);         /*All clear*/
}


/**
*@brief   This function established  the connection for the channel in passive (server) mode.
*     This function waits for the request from the peer.
*@param   s: socket number.
*@return  1 for success else 0.
*/
uint8_t listen(SOCKET s)
{
   uint8_t ret;
   if (w5500_read_byte( Sn_SR(s) ) == SOCK_INIT)
   {
      w5500_write_byte( Sn_CR(s) ,Sn_CR_LISTEN);

      while( w5500_read_byte(Sn_CR(s) ) )         /*Wait to process the command*/
         ;
      ret = 1;
   }
   else
   {
      ret = 0;
   }
   return ret;
}

/**
*@brief   This function established  the connection for the channel in Active (client) mode.
*     This function waits for the untill the connection is established.
*@param   s: socket number.
*@param   addr: The server IP address to connect.
*@param   port: The server IP port to connect.
*@return    1 for success else 0.
*/
uint8_t connect(SOCKET s, uint8_t * addr, uint16_t port)
{
    uint8_t ret;
    if
        (
            ((addr[0] == 0xFF) && (addr[1] == 0xFF) && (addr[2] == 0xFF) && (addr[3] == 0xFF)) ||
            ((addr[0] == 0x00) && (addr[1] == 0x00) && (addr[2] == 0x00) && (addr[3] == 0x00)) ||
            (port == 0x00)
        )
    {
      ret = 0;
    }
    else
    {
        ret = 1;
        w5500_write_byte( Sn_DIPR0(s), addr[0]);
        w5500_write_byte( Sn_DIPR1(s), addr[1]);
        w5500_write_byte( Sn_DIPR2(s), addr[2]);
        w5500_write_byte( Sn_DIPR3(s), addr[3]);
        w5500_write_byte( Sn_DPORT0(s), (uint8_t)((port & 0xff00) >> 8));
        w5500_write_byte( Sn_DPORT1(s), (uint8_t)(port & 0x00ff));
        w5500_write_byte( Sn_CR(s) ,Sn_CR_CONNECT);

        while ( w5500_read_byte(Sn_CR(s) ) ) ;              /*Wait for completion*/

        while ( w5500_read_byte(Sn_SR(s)) != SOCK_SYNSENT )
        {
            if(w5500_read_byte(Sn_SR(s)) == SOCK_ESTABLISHED)
            {
                break;
            }
            if (getSn_IR(s) & Sn_IR_TIMEOUT)
            {
                w5500_write_byte(Sn_IR(s), (Sn_IR_TIMEOUT));        /*Clear TIMEOUT Interrupt*/
                ret = 0;
                break;
            }
        }
    }

   return ret;
}

/**
*@brief   This function used for disconnect the socket s.
*@param   s: socket number.
*@return    1 for success else 0.
*/
void disconnect(SOCKET s)
{
   w5500_write_byte( Sn_CR(s) ,Sn_CR_DISCON);

   while( w5500_read_byte(Sn_CR(s) ) )                   /*Wait to process the command*/
      ;
}

/**
*@brief   This function used to send the data in TCP mode
*@param   s: socket number.
*@param   buf: data buffer to send.
*@param   len: data length.
*@return  1 for success else 0.
*/
uint16_t send(SOCKET s, const uint8_t * buf, uint16_t len)
{
  uint8_t status=0;
  uint16_t ret=0;
  uint16_t freesize=0;

  if (len > getIINCHIP_TxMAX(s)) ret = getIINCHIP_TxMAX(s);     /*Check size not to exceed MAX size*/
  else ret = len;

  do
  {
    freesize = getSn_TX_FSR(s);
    status = w5500_read_byte(Sn_SR(s));
    if ((status != SOCK_ESTABLISHED) && (status != SOCK_CLOSE_WAIT))
    {
      ret = 0;
      break;
    }
  } while (freesize < ret);

  send_data_processing(s, (uint8_t *)buf, ret);            /*Copy data*/
  w5500_write_byte( Sn_CR(s) ,Sn_CR_SEND);
                                     /*Wait to process the command*/
  while( w5500_read_byte(Sn_CR(s) ) );

  while ( (w5500_read_byte(Sn_IR(s) ) & Sn_IR_SEND_OK) != Sn_IR_SEND_OK )
  {
    status = w5500_read_byte(Sn_SR(s));
    if ((status != SOCK_ESTABLISHED) && (status != SOCK_CLOSE_WAIT) )
    {
    //  printf("SEND_OK Problem!!\r\n");
      close(s);
      return 0;
    }
  }
  w5500_write_byte( Sn_IR(s) , Sn_IR_SEND_OK);

#ifdef __DEF_IINCHIP_INT__
   putISR(s, getISR(s) & (~Sn_IR_SEND_OK));
#else
   w5500_write_byte( Sn_IR(s) , Sn_IR_SEND_OK);
#endif

   return ret;
}

/**
*@brief   This function is an application I/F function which is used to receive the data in TCP mode.
*     It continues to wait for data as much as the application wants to receive.
*@param   s: socket number.
*@param   buf: data buffer to receive.
*@param   len: data length.
*@return    received data size for success else 0.
*/
uint16_t recv(SOCKET s, uint8_t * buf, uint16_t len)
{
   uint16_t ret=0;
   if ( len > 0 )
   {
      recv_data_processing(s, buf, len);
      w5500_write_byte( Sn_CR(s) ,Sn_CR_RECV);

      while( w5500_read_byte(Sn_CR(s) ));                /*Wait to process the command*/
      ret = len;
   }
   return ret;
}

/**
*@brief   This function is an application I/F function which is used to send the data for other then TCP mode.
*     Unlike TCP transmission, The peer's destination address and the port is needed.
*@param   s: socket number.
*@param   buf: data buffer to send.
*@param   len: data length.
*@param   addr: IP address to send.
*@param   port: IP port to send.
*@return    This function return send data size for success else 0.
*/
uint16_t sendto(SOCKET s, const uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t port)
{
   uint16_t ret=0;

   if (len > getIINCHIP_TxMAX(s))
   ret = getIINCHIP_TxMAX(s);                     /*Check size not to exceed MAX size*/
   else ret = len;

   if( ((addr[0] == 0x00) && (addr[1] == 0x00) && (addr[2] == 0x00) && (addr[3] == 0x00)) || ((port == 0x00)) )//||(ret == 0) )
   {
      ret = 0;
   }
   else
   {
      w5500_write_byte( Sn_DIPR0(s), addr[0]);
      w5500_write_byte( Sn_DIPR1(s), addr[1]);
      w5500_write_byte( Sn_DIPR2(s), addr[2]);
      w5500_write_byte( Sn_DIPR3(s), addr[3]);
      w5500_write_byte( Sn_DPORT0(s),(uint8_t)((port & 0xff00) >> 8));
      w5500_write_byte( Sn_DPORT1(s),(uint8_t)(port & 0x00ff));
      send_data_processing(s, (uint8_t *)buf, ret);           /*Copy data*/
      w5500_write_byte( Sn_CR(s) ,Sn_CR_SEND);

      while( w5500_read_byte( Sn_CR(s) ) )                  /*Wait to process the command*/
    ;
     while( (w5500_read_byte( Sn_IR(s) ) & Sn_IR_SEND_OK) != Sn_IR_SEND_OK )
     {
      if (w5500_read_byte( Sn_IR(s) ) & Sn_IR_TIMEOUT)
      {
      w5500_write_byte( Sn_IR(s) , (Sn_IR_SEND_OK | Sn_IR_TIMEOUT));  /*Clear SEND_OK & TIMEOUT*/
      return 0;
      }
     }
      w5500_write_byte( Sn_IR(s) , Sn_IR_SEND_OK);
   }
   return ret;
}

/**
*@brief   This function is an application I/F function which is used to receive the data in other then
*     TCP mode. This function is used to receive UDP, IP_RAW and MAC_RAW mode, and handle the header as well.
*@param   s: socket number.
*@param   buf: data buffer to receive.
*@param   len: data length.
*@param   addr: IP address to receive.
*@param   port: IP port to receive.
*@return  This function return received data size for success else 0.
*/
uint16_t recvfrom(SOCKET s, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t *port)
{
   uint8_t head[8];
   uint16_t data_len=0;
   uint16_t ptr=0;
   uint32_t addrbsb =0;
   if ( len > 0 )
   {
      ptr     = w5500_read_byte(Sn_RX_RD0(s) );
      ptr     = ((ptr & 0x00ff) << 8) + w5500_read_byte(Sn_RX_RD1(s));
      addrbsb = (uint32_t)(ptr<<8) +  (s<<5) + 0x18;

      switch (w5500_read_byte(Sn_MR(s) ) & 0x07)
      {
      case Sn_MR_UDP :
        w5500_read_buf(addrbsb, head, 0x08);
        ptr += 8;
        /*Read peer's IP address, port number*/
        addr[0]  = head[0];
        addr[1]  = head[1];
        addr[2]  = head[2];
        addr[3]  = head[3];
        *port    = head[4];
        *port    = (*port << 8) + head[5];
        data_len = head[6];
        data_len = (data_len << 8) + head[7];

        addrbsb = (uint32_t)(ptr<<8) +  (s<<5) + 0x18;
        w5500_read_buf(addrbsb, buf, data_len);
        ptr += data_len;

        w5500_write_byte( Sn_RX_RD0(s), (uint8_t)((ptr & 0xff00) >> 8));
        w5500_write_byte( Sn_RX_RD1(s), (uint8_t)(ptr & 0x00ff));
        break;

      case Sn_MR_IPRAW :
        w5500_read_buf(addrbsb, head, 0x06);
        ptr += 6;
        addr[0]  = head[0];
        addr[1]  = head[1];
        addr[2]  = head[2];
        addr[3]  = head[3];
        data_len = head[4];
        data_len = (data_len << 8) + head[5];

    addrbsb  = (uint32_t)(ptr<<8) +  (s<<5) + 0x18;
        w5500_read_buf(addrbsb, buf, data_len);
        ptr += data_len;

    w5500_write_byte( Sn_RX_RD0(s), (uint8_t)((ptr & 0xff00) >> 8));
        w5500_write_byte( Sn_RX_RD1(s), (uint8_t)(ptr & 0x00ff));
        break;

      case Sn_MR_MACRAW :
        w5500_read_buf(addrbsb, head, 0x02);
        ptr+=2;
        data_len = head[0];
        data_len = (data_len<<8) + head[1] - 2;
        if(data_len > 1514)
        {
       //    printf("data_len over 1514\r\n");
           while(1);
        }
        addrbsb  = (uint32_t)(ptr<<8) +  (s<<5) + 0x18;
        w5500_read_buf(addrbsb, buf, data_len);
        ptr += data_len;

        w5500_write_byte( Sn_RX_RD0(s), (uint8_t)((ptr & 0xff00) >> 8));
        w5500_write_byte( Sn_RX_RD1(s), (uint8_t)(ptr & 0x00ff));
        break;

      default :
            break;
      }
      w5500_write_byte( Sn_CR(s) ,Sn_CR_RECV);

      while( w5500_read_byte( Sn_CR(s)) ) ;             /*Wait to process the command*/
   }
   return data_len;
}

#ifdef __MACRAW__

/**
*@brief   OPen the 0-th socket with MACRAW mode.
*@param   None
*@return  None
*/
void macraw_open(void)
{
  uint8_t sock_num=0;
  uint16_t dummyPort = 0;
  uint8_t mFlag = 0;
  sock_num = 0;
  close(sock_num);                          /*Close the 0-th socket*/
  socket(sock_num, Sn_MR_MACRAW, dummyPort,mFlag);
}

/**
*@brief   OPen the 0-th socket with MACRAW mode.
*@param   buf: data buffer to send.
*@param   len: data length.
*@return  This function return sended data size for success else 0.
*/
uint16_t macraw_send( const uint8_t * buf, uint16_t len )
{
   uint16_t ret=0;
   uint8_t sock_num;
   sock_num =0;

   if (len > getIINCHIP_TxMAX(sock_num)) ret = getIINCHIP_TxMAX(sock_num);    /*Check size not to exceed MAX size*/
   else ret = len;
   send_data_processing(sock_num, (uint8_t *)buf, len);

   w5500_write_byte(Sn_CR(sock_num),Sn_CR_SEND);                  /*W5500 send command*/
   while( w5500_read_byte(Sn_CR(sock_num)) );
   while ( (w5500_read_byte(Sn_IR(sock_num)) & Sn_IR_SEND_OK) != Sn_IR_SEND_OK );
   w5500_write_byte(Sn_IR(sock_num), Sn_IR_SEND_OK);

   return ret;
}

/**
*@brief   OPen the 0-th socket with MACRAW mode.
*@param   buf: data buffer to send.
*@param   len: data length.
*@return  This function return received data size for success else 0.
*/
uint16_t macraw_recv( uint8_t * buf, uint16_t len )
{
   uint8_t sock_num;
   uint16_t data_len=0;
   uint16_t dummyPort = 0;
   uint16_t ptr = 0;
   uint8_t mFlag = 0;
   sock_num = 0;

   if ( len > 0 )
   {
      data_len = 0;

      ptr = w5500_read_byte(Sn_RX_RD0(sock_num));
      ptr = (uint16_t)((ptr & 0x00ff) << 8) + w5500_read_byte( Sn_RX_RD1(sock_num) );

      data_len = w5500_read_byte_RXBUF(0, ptr);           /*Read_data(s, (uint8_t *)ptr, data, len) & read data*/
      ptr++;
      data_len = ((data_len<<8) + w5500_read_byte_RXBUF(0, ptr)) - 2;
      ptr++;

      if(data_len > 1514)
      {
        // printf("data_len over 1514\r\n");
        // printf("\r\nptr: %X, data_len: %X", ptr, data_len);

         close(sock_num);                       /*Close the 0-th socket*/
         socket(sock_num, Sn_MR_MACRAW, dummyPort,mFlag);       /*OPen the 0-th socket with MACRAW mode*/
         return 0;
      }
      w5500_read_byte_RXBUF_BURST(sock_num, ptr, data_len, (uint8_t*)(buf));
      ptr += data_len;

      w5500_write_byte(Sn_RX_RD0(sock_num),(uint8_t)((ptr & 0xff00) >> 8));
      w5500_write_byte(Sn_RX_RD1(sock_num),(uint8_t)(ptr & 0x00ff));
      w5500_write_byte(Sn_CR(sock_num), Sn_CR_RECV);
      while( w5500_read_byte(Sn_CR(sock_num)) ) ;
   }
   return data_len;
}
#endif
