
#include "rgauss.h"
#include "mt19937ar.h"

int int_rgauss( float moyenne, float sd)
{
    float rgau= -6.0;
    
    for(int i=1;i<=12;i++)
    {
      rgau+=genrand_real1();     
    }
    
    rgau=rgau*sd+moyenne;
    
    return int(rgau);
}



float float_rgauss( float moyenne, float sd)
{
    float rgau= -6.0;
    
    for(int i=1;i<=12;i++)
    {
      rgau+=genrand_real1();     
    }
    
    rgau=rgau*sd+moyenne;
    
    return rgau;
}

int int_gauss_distrib( float moyenne, float demilargeur)
{
    float rgau= -6.0;
    float sd=demilargeur/3;
    
    for(int i=1;i<=12;i++)
    {
      rgau+=genrand_real1();     
    }
    
    rgau=rgau*sd+moyenne;
    
    return int(rgau);
}
