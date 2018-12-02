/*
 */
#ifndef I2CADDR_H_
#define I2CADDR_H_

#if defined(BOARD1)
#define I2C_SLAVE_ADDR 0x41
#elif defined(BOARD2)
#define I2C_SLAVE_ADDR 0x42
#elif defined(BOARD3)
#define I2C_SLAVE_ADDR 0x43
#elif defined(BOARD4)
#define I2C_SLAVE_ADDR 0x44
#elif defined(BOARD5)
#define I2C_SLAVE_ADDR 0x45
#elif defined(BOARD6)
#define I2C_SLAVE_ADDR 0x46
#else
#define I2C_SLAVE_ADDR 0x48
#endif

#endif /* I2CADDR_H_ */
