#include "bno08x_uart_rvc.h"

void update_bno(BNO08x_t *bno, const uint8_t *sorted_buffer)
{
  bno->yaw = ((int16_t)(sorted_buffer[4] << 8) | sorted_buffer[3]) * DEGREE_SCALE;
  bno->pitch = ((int16_t)(sorted_buffer[6] << 8) | sorted_buffer[5]) * DEGREE_SCALE;
  bno->roll = ((int16_t)(sorted_buffer[8] << 8) | sorted_buffer[7]) * DEGREE_SCALE;
  bno->accel_X = ((int16_t)(sorted_buffer[10] << 8) | sorted_buffer[9]) * MILLI_G_TO_MMS2;
  bno->accel_Y = ((int16_t)(sorted_buffer[12] << 8) | sorted_buffer[11]) * MILLI_G_TO_MMS2;
  bno->accel_Z = ((int16_t)(sorted_buffer[14] << 8) | sorted_buffer[13]) * MILLI_G_TO_MMS2;
}

void sort_buffer(const uint8_t *buffer, uint8_t *sorted_buffer)
{
  uint8_t first_index = BUFFER_LENGTH + 1;
  for (uint8_t i = 0; i < BUFFER_LENGTH; i++)
  {
    if (i != BUFFER_LENGTH - 1)
    {
      if (buffer[i] == START_CHAR && buffer[i + 1] == START_CHAR)
      {
        first_index = i;
        break;
      }
    }
    else
    {
      if (buffer[BUFFER_LENGTH - 1] == START_CHAR && buffer[0] == START_CHAR)
      {
        first_index = BUFFER_LENGTH - 1;
        break;
      }
    }
  }
  if (first_index != BUFFER_LENGTH + 1)
  {
    for (uint8_t i = first_index, j = 0; i < BUFFER_LENGTH; i++, j++)
    {
      sorted_buffer[j] = buffer[i];
    }

    for (uint8_t i = 0, j = BUFFER_LENGTH - first_index; i < first_index; i++, j++)
    {
      sorted_buffer[j] = buffer[i];
    }
  }
  else
  {
    //? Data header is not available
    for (uint8_t i = 0; i < BUFFER_LENGTH; i++)
    {
      sorted_buffer[i] = 0;
    }
  }
}
