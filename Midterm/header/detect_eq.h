//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
	    direction = 0;
	    amplitude = 0;
	    first = 0;
	    detect_eq_state = DEQCapture;
            break;
	case DEQCapture:
	    detect_eq_state = DEQCapture;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
	case DEQCapture:
            amplitude = (PINA >> 3) & 0x1F;
	    if(amplitude == 0) {
		    detected = 0;
            } else {
		    detected = 1;
		    direction = PINA | 0x03;
	    }

	    break;
        default:
            break;
    }
}
