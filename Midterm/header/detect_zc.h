
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
static unsigned char east = 0x00;
static unsigned char nEast = 0x01;
static unsigned char north = 0x02;
static unsigned char nWest = 0x03;

static unsigned char west = 0x04;
static unsigned char sWest = 0x05;
static unsigned char south = 0x06;
static unsigned char sEast = 0x07;

/*complete the state machine*/

void Detect_ZC()
{
    switch(detect_zc_state)
    {
        case DZCInit:
		detect_zc_state = DZCFirst;
            break;
	case DZCFirst:
    		detect_zc_state = DZCSecond;
    		break;
	case DZCSecond:
		detect_zc_state = DZCFirst;
		break;		
        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit:
		first = direction;
            break;
	case DZCFirst: 
	    break;
	case DZCSecond:
		if((first == east && direction == west) || (first == nEast && direction == sWest) || (first == north && direction == south) || (first == nWest && direction == sEast) || (first == west && direction == east) || (first == sWest && direction == nEast) || (first == south && direction == north) || (first == sEast && direction == nWest)) {
			zero_crossing = 1;
		} else {
			zero_crossing = 0;
		}
		first = direction;
		break;
        default:	
            break;
    }
}
