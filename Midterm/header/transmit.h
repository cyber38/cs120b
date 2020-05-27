//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Transmit()
{
    switch(transmit_state)
    {
        case TInit:
		transmit_state = TOutput;
            break;
	case TOutput:
	    	transmit_state = TOutput;
		break;
        default:
            transmit_state = TInit;
            break;
    }
    switch(transmit_state)
    {
        case TInit:
            break;
	case TOutput:
	    PORTB = PINB | ping | (detected << 1) | (zero_crossing << 2) | (max << 3);
        default:
            break;
    }

}
