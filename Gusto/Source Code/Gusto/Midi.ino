#define MIDI_BAUD_RATE 31250
#define MIDI_DEFAULT_CHANNEL 15

#define MIDI_CC_COMMAND_BYTE 0x0B
#define MIDI_PC_COMMAND_BYTE 0x0C

byte ChannelNumber = MIDI_DEFAULT_CHANNEL;

void InitialiseMidi()
{
  Serial.begin(MIDI_BAUD_RATE);
  while(!Serial);
}

void CheckMidi()
{
  do
  {
    if (Serial.available())
    {
      //read first byte
      byte commandByte = Serial.read();
      // example command byte = 76543210.
      // 3210 represents the channel, i.e. channel 10 would be 1010.
      // 7654 represents the type of command, i.e. 1011 is a control change, 1100 is a program change.
    
      byte command = commandByte >> 4;
      byte channel = commandByte - (command << 4);
    
      //read next byte
      byte secondByte = Serial.read();
      
      switch (command)
      {
        case MIDI_CC_COMMAND_BYTE:
        {
          byte controlNumber = secondByte;
          
          // Check that we have at least one byte available containing a value
          if (Serial.available() > 1)
          {
            //read final byte
            ControlChange(controlNumber, Serial.read());
          } 
          break;
        }
        case MIDI_PC_COMMAND_BYTE:
        {
          ProgramChange(secondByte);
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
  while (Serial.available() > 2);
}

void ControlChange(byte controlNumber, byte changeValue)
{
  //TempoBpm
  //TapDivision (0=quarter, 64=eighth, 127=dottedEighth)
  //ModSpeedHz (1-127, desiredValue=value/20, i.e. to set a speed of 0.5, send a value of 10)
  //ModDepth (1-127, desiredValue=value/20, i.e. to set a depth of 0.5, send a value of 10)
  //ModToggle (0=off, 127=on)
  //ModMode (0=light, 127=deep)
  //SavePreset (0-9, saves the current settings to the given preset value)
}

void ProgramChange(byte programNumber)
{
  //RecallPreset (0-9, recalls the preset from the given preset value)
}

