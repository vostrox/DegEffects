void CheckMidi()
{
  do
  {
    if (Serial1.available())
    {
      //read first byte
      byte commandByte = Serial1.read();
      // example command byte = 76543210.
      // 3210 represents the channel, i.e. channel 10 would be 1010.
      // 7654 represents the type of command, i.e. 1011 is a control change, 1100 is a program change.
    
      byte command = commandByte >> 4;
      byte channel = commandByte - (command << 4);
    
      //read next byte
      byte secondByte = Serial1.read();
      
      switch (command)
      {
        case ControlChangeByte:
        {
          byte controlNumber = secondByte;
          
          // Check that we have at least one byte available and that this message is a control change
          if ((Serial1.available() > 1) && command == ControlChangeByte)
          {
            //read final byte
            byte changeValue = Serial1.read();
          } 
          break;
        }
        case ProgramChangeByte:
        {
          byte programNumber = secondByte;
          break;
        }
      }
      
      if (channel == ChannelNumber)
      {
        //do something with the data
      }
    }
  }
  //when at least two bytes available
  while (Serial1.available() > 2);
}
