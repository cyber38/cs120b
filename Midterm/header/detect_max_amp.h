
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
		detect_max_amp_state = DMACheck;
            break;
        case DMACheck:
		detect_max_amp_state = DMACheck;
		break;
        default:
		detect_max_amp_state = DMAInit;
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	case DMACheck:
	    if(amplitude > max) {
		    max = amplitude;
	    }
	    break;
        default:
            break;
    }
}
