void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int max1;
int max2;

void BiLinear(int a, int b, int c, int d) {
  
  max1 = max(max(a,b), max(c,d));

  if (max(a,b) < max(c,d)) 
  {
    if (max(a,b) > c || max(a,b) > d) 
    {
      max2 = max(a,b);
    }  
     else if (c > d)
     {
       max2 = d;
     }
     else 
     {
      max2 = c;
     }  
  }
  else 
  {
    if (max(c,d) > a || max(c,d) > b) 
    {
      max2 = max(c,d);
    } 
     else if (a > b) 
     {
      max2 = b;
     }
     
     else 
     {
      max2 = a;
     }
   }

  Serial.print(max1, max2);
}

void loop() {
  // put your main code here, to run repeatedly:
  BiLinear(1,2,3,4);
}
