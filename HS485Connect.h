#pragma platform(NXT)

ubyte iRezult;

task Receive()
{
	const int kHexDigitsPerLine = 8;

	int nNumbBytesAvail;
	int nNumbBytesToRead;
	int nNumbBytesActuallyRead;
	byte BytesRead[kHexDigitsPerLine];
	while (true)
	{
		//nxtDisplayTextLine(7,"%d",iRezult);
	  //
	  // Loop continuously, reading one byte at a time. The interface will support larger reads.
	  //
		nNumbBytesAvail = nxtGetAvailHSBytes();
		if (nNumbBytesAvail <= 0)
		{
		// nNumbBytesActuallyRead = 0;
			wait1Msec(3);
			continue;
		}

		if (nNumbBytesAvail < sizeof(BytesRead))
		  nNumbBytesToRead = nNumbBytesAvail;
		else
		  nNumbBytesToRead = sizeof(BytesRead);
		nNumbBytesActuallyRead = nxtReadRawHS((ubyte*)BytesRead, nNumbBytesToRead);
    //nRcvChars += nNumbBytesActuallyRead;
		wait1Msec(3);
	  //
	  // Display the last eight bytes read on the NXT LCD in hex format.
	  //
		//
		// Display progress results on the NXT LCD screen.
		//

	  //
	  // Display the  bytes read on the NXT LCD in hex format.
	  //
	//saf  const int kHexDigitsPerLine = 8;
   	//iRezult = ( BytesRead[0] > 0 ) ? BytesRead[0] : 256 + BytesRead[0] ;
    	iRezult = (ubyte)BytesRead[0];
	  //nxtDisplayTextLine(7,"%d",iRezult);
	}
}


void setupHighSpeedLink()
{
	iRezult = 0;
	nxtEnableHSPort();
	nxtHS_Mode = hsRawMode;
	StartTask(Receive);
	return;
}

void Transmit(ubyte nData)
{
	char data[1];
	data[0] = nData;
  int i = 0;
	while ((nxtWriteRawHS(data, sizeof(nData), 0) != ioRsltSuccess) && ((i++)<8)) //saf;
  	wait1Msec(3); // To reduce the screen flicker
}
