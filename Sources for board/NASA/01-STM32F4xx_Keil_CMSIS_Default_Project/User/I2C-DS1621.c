/*
 * I2C-DS1621.c
 *
 *  Created on: Mar 19, 2013
 *      Author: patricio
 */

#include "I2C-DS1621.h"

int8_t Temperature[2];

/*******************************************************************************
* Function Name  : I2C_Configuration
* Description    :
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/



void DS1621_WriteData (uint8_t data) {

  // wait until I2C1 is not busy anymore
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  // Send I2C1 START condition
  I2C_GenerateSTART(I2C1, ENABLE);
  // wait for I2C1 EV5 --> Slave has acknowledged start condition
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  // Send slave Address:
  I2C_Send7bitAddress(I2C1, 0x90,  I2C_Direction_Transmitter);
  //wait for I2C1 EV6, check if Slave has acknowledged Master transmitter mode
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_SendData(I2C1, data);
  // wait for I2C1 EV8_2 --> byte has been transmitted
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  // Send I2C1 STOP Condition
  I2C_GenerateSTOP(I2C1, ENABLE);

}

void DS1621_SendCommand (uint8_t cmd, uint8_t direction) {

  // wait until I2C1 is not busy anymore
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  // Send I2C1 START condition
  I2C_GenerateSTART(I2C1, ENABLE);
  // wait for I2C1 EV5 --> Slave has acknowledged start condition
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  // Send slave Address:
  I2C_Send7bitAddress(I2C1, 0x90,  direction);
  //wait for I2C1 EV6, check if Slave has acknowledged Master transmitter mode
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_SendData(I2C1, cmd);
  // wait for I2C1 EV8_2 --> byte has been transmitted
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  // Send I2C1 STOP Condition
  I2C_GenerateSTOP(I2C1, ENABLE);
}





void DS1621_ReadTemp (int8_t ptemperature_data[]) {
  // Get temperature:

  // wait until I2C1 is not busy anymore
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  // Send I2C1 START condition
  I2C_GenerateSTART(I2C1, ENABLE);
  // wait for I2C1 EV5 --> Slave has acknowledged start condition
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  // Send slave Address:
  //I2C_Send7bitAddress(I2C1, 0x90,  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
  I2C_Send7bitAddress(I2C1, 0x90,  I2C_Direction_Receiver);
  //wait for I2C1 EV6, check if Slave has acknowledged Master receiver mode
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  // enable acknowledge of recieved data:
  I2C_AcknowledgeConfig(I2C1, ENABLE);
  // wait until one byte has been received
  while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) );
  // read data from I2C data register
  ptemperature_data[0] = I2C_ReceiveData(I2C1);


  // disabe acknowledge for the second byte
  I2C_AcknowledgeConfig(I2C1, DISABLE);
  // wait until one byte has been received
  while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) );
  // read data from I2C data register
  ptemperature_data[1] = I2C_ReceiveData(I2C1);


  // Send I2C1 STOP Condition
  I2C_GenerateSTOP(I2C1, ENABLE);
}


void DS1621_ReadData (int8_t* data) {
  // Get temperature:

  // wait until I2C1 is not busy anymore
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  // Send I2C1 START condition
  I2C_GenerateSTART(I2C1, ENABLE);
  // wait for I2C1 EV5 --> Slave has acknowledged start condition
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  // Send slave Address:
  //I2C_Send7bitAddress(I2C1, 0x90,  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
  I2C_Send7bitAddress(I2C1, 0x90,  I2C_Direction_Receiver);
  //wait for I2C1 EV6, check if Slave has acknowledged Master receiver mode
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  // enable acknowledge of recieved data:
  //I2C_AcknowledgeConfig(I2C1, ENABLE);
  // wait until one byte has been received
  while( !I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) );
  // read data from I2C data register
  *data = I2C_ReceiveData(I2C1);

  // disabe acknowledge for the second byte
  I2C_AcknowledgeConfig(I2C1, DISABLE);


  // Send I2C1 STOP Condition
  I2C_GenerateSTOP(I2C1, ENABLE);
}




