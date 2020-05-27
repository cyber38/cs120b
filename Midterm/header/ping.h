
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char l = 0;
static unsigned char h = 0;


/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit:
		l = 0;
		h = 0;
		ping_state = PIhigh;
            break;
	case PIlow:
	    	if(l < 9) {
			ping_state = PIlow;
		} else {
	        	ping_state = PIhigh;
		}
	    break;
	case PIhigh:
	    	if(h < 1) {
	    		ping_state = PIhigh;
		} else {
			h = 0;
			ping_state = PIlow;
		}
	    break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;
	case PIlow:
	    ping = 0x00;
            ++l;
	    break;
	case PIhigh:
	    ping = 0x01;
	    ++h;
	    break;
        default:
            break;
    }
}
