
unsigned short us_Power = 1000U;
unsigned long us_timeCount = 0;

int ibit() {

    if (us_Power <= 200U) 
    {
        /*Change State to EMERGENCY*/
        return (9U);
    } 
    else if (us_Power <= 500U) 
    {
        /*Change State to FAIL*/
        return (3U);
    } 
    else 
    {
        while (1) 
        {
            us_timeCount++;

            if (us_timeCount > 5U) 
            {
                /*Change State to READY*/
                return (4U);
            }
        }
    }
}