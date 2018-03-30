1���޷��˲���***************************************************
 *�������ƣ�AmplitudeLimiterFilter()-�޷��˲���
 *�ŵ㣺����Ч�˷���żȻ����������������
 *ȱ�㣺�޷��������������Եĸ��ţ���ƽ���Ȳ�
 *˵����
 1�����ú���
 GetAD(),�ú�������ȡ�õ�ǰֵ
 2������˵��
 Value:���һ����Ч������ֵ���ñ���Ϊȫ�ֱ���
 NewValue:��ǰ������ֵ
 ReturnValue:����ֵ
 3������˵��
 A:���β�����������ֵ����ֵ��Ҫʹ���߸���ʵ���������
 *��ڣ�Value,��һ����Ч�Ĳ���ֵ�����������︳ֵ
 *���ڣ�ReturnValue,����ֵ�������˲����
 ****************************************************/
 #define A 10
 unsigned char Value
 unsigned char AmplitudeLimiterFilter()
 {
 unsigned char NewValue;
 unsigned char ReturnValue;
 NewValue=GatAD();
 if(((NewValue-Value)>A))||((Value-NewValue)>A)))
 ReturnValue=Value;
 else ReturnValue=NewValue;
 return(ReturnValue);
 }
 2����λֵ�˲���

 /****************************************************
 *�������ƣ�MiddlevalueFilter()-��λֵ�˲���
 *�ŵ㣺����Ч�˷���żȻ��������Ĳ������ţ����¶ȡ�Һ
 λ�ȱ仯�����ı�����������õ��˲�Ч��
 *ȱ�㣺���������ٶȵȿ��ٱ仯�Ĳ�������
 *˵����
 1�����ú���
 GetAD(),�ú�������ȡ�õ�ǰֵ
 Delay(),������ʱ����
 2������˵��
 ArrDataBuffer[N]:�������һ���Բɼ���N������
 Temp:���ð�ݷ����õ���ʱ�Ĵ���
 i,j,k:ѭ�����õĲ���ֵ
 3������˵��
 N�����鳤��
 *��ڣ�
 *���ڣ�value_buf[(N-1)/2],����ֵ�������˲����
 *****************************************************/

 #define N 11

 unsigned char MiddlevalueFilter()

 {
 unsigned char value_buf[N];
 unsigned char i,j,k,temp;
 for(i=0;i<N;i++)
 {
 value_buf[i] = get_ad();
 delay();
 }
 for (j=0;j<N-1;j++)
 {
 for (k=0;k<N-j;k++)
 {
 if(value_buf[k]>value_buf[k+1])
 {
 temp = value_buf[k];
 value_buf[k] = value_buf[k+1];
 value_buf[k+1] = temp;
 }
 }
 }
 return value_buf[(N-1)/2];
 }


 3������ƽ���˲���

 /*********************************************************
 ˵��������ȡN������ֵ��������ƽ������
 �ŵ㣺�����ڶ�һ�����������ŵ��źŽ����˲��������źŵ��ص���
 ��һ��ƽ��ֵ���ź���ĳһ��ֵ��Χ�������²�����
 ȱ�㣺���ڲ����ٶȽ�����Ҫ�����ݼ���Ͽ��ʵʱ���Ʋ����á�
 **********************************************************/

 #define N 12

 char filter()
 {
 unsigned int sum = 0;
 unsigned char i;

 for (i=0;i<N;i++)
 {
 sum + = get_ad();
 delay();
 }
 return(char)(sum/N);
 }

 4������ƽ���˲������ֳƻ���ƽ���˲�����

 /***************************************************
 ˵����������N������ֵ����һ�����У����г��ȹ̶�ΪN��
 ÿ�β�����һ�������ݷ����β�����ӵ����׵�һ
 �����ݡ��Ѷ����е�N�����ݽ���ƽ�����㣬�Ȼ��
 �µ��˲������
 �ŵ㣺�������Ը��������õ��������ã�ƽ���ȸߣ������ڸ�Ƶ�񵴵�ϵͳ
 ȱ�㣺�����ȵͣ���żȻ���ֵ������Ը��ŵ��������ýϲ�����������
 �Ž����صĳ���
 ****************************************************/

 #define N 12

 unsigned char value_buf[N];

 unsigned char filter()
 {
 unsigned char i;
 unsigned char value;
 int sum=0;

 value_buf[i++] = get_ad(); //�ɼ��������ݷ������λ
 for(i=0;i<N;i++)
 {
 value_buf[i]=value_buf[i+1]; //�����������ƣ���λ�ӵ�
 sum += value_buf[i];
 }
 value = sum/N;
 return(value);
 }

 5����λֵƽ���˲������ֳƷ��������ƽ���˲�����

 /********************************************
 ˵������һ�����ȥ�����ֵ����Сֵ
 �ŵ㣺�ں��������˲����ŵ㡣����żȻ���ֵ������Ը��ţ�����
 ����������Ĳ���ֵƫ������ڸ��������õ��������ã�
 ƽ���ȸߣ����ڸ�Ƶ�񵴵�ϵͳ��
 ȱ�㣺�����ٶ���
 *********************************************/

 #define N 12

 uchar filter()

 {
 unsigned char i,j,k,l;
 unsigned char temp,sum=0,value;
 unsigned char value_buf[N],;

 for(i=0;i<N;i++)
 {
 value_buf[i] = get_ad();
 delay();
 }
 //����ֵ��С�������У�ð�ݷ���
 for(j=0;j<N-1;j++)
 {
 for(i=0;i<N-j;i++)
 {
 if(value_buf[i]>value_buf[i+1])
 {
 temp = value_buf[i];
 value_buf[i] = value_buf[i+1];
 value_buf[i+1] = temp;
 }
 }
 }

 for(i=1;i<N-1;i++)
 sum += value_buf[i];

 value = sum/(N-2);
 return(value);
 }

 6��������λֵ�˲���
 /************************************************
 �ŵ㣺����żȻ���ֵ������Ը��ţ���������������Ĳ���ֵƫ�
 �������Ը��������õ��������ã�ƽ���ȸߣ������ڸ�Ƶ��
 ��ϵͳ
 ȱ�㣺�����ٶ���
 *************************************************/

 char filter(char new_data,char queue[],char n)
 {
 char max,min;
 char sum;
 char i;

 queue[0]=new_data;
 max=queue[0];
 min=queue[0];
 sum=queue[0];

 for(i=n-1;i>0;i--)
 {
 if(queue[i]>max)
 max=queue[i];
 else if (queue[i]<min)
 min=queue[i];
 sum=sum+queue[i];
 queue[i]=queue[i-1];
 }

 i=n-2;
 sum=sum-max-min+i/2; //˵����+i/2��Ŀ����Ϊ����������
 sum=sum/i;

 return(sum);
 }

 7���޷�ƽ���˲���

 /************************************************
 �ŵ㣺����żȻ���ֵ������Ը��ţ���������������Ĳ���ֵƫ�
 *************************************************/
 #define A 10
 #define N 12

 unsigned char data[];
 unsigned char filter(data[])
 {
 unsigned char i;
 unsigned char value,sum;

 data[N]=GetAD();
 if(((data[N]-data[N-1])>A||((data[N-1]-data[N])>A))
 data[N]=data[N-1];
 //else data[N]=NewValue;
 for(i=0;i<N;i++)
 {
 data[i]=data[i+1];
 sum+=data[i];
 }
 value=sum/N;
 return(value);
 }


 8��һ���ͺ��˲���

 /****************************************************
 *�������ƣ�filter()-һ���ͺ��˲���
 *˵����
 1�����ú���
 GetAD(),�ú�������ȡ�õ�ǰֵ
 Delay(),������ʱ����
 2������˵��
 Or_data[N]:�ɼ�������
 Dr0_flag��Dr1_flag:ǰһ�αȽ��뵱ǰ�Ƚϵķ���λ
 coeff:�˲�ϵ��
 F_count���˲�������
 3������˵��
 N�����鳤��
 Thre_value���Ƚ��ż�ֵ
 *��ڣ�
 *���ڣ�
 *****************************************************/

 #define Thre_value 10
 #define N 50

 float Or_data[N]��
 unsigned char Dr0_flag=0,Dr1_flag=0;

 void abs(float first,float second)
 {
 float abs;
 if(first>second)
 {
 abs=first-second;
 Dr1_flag=0;
 }
 else
 {
 abs=second-first;
 Dr1_flag=1;
 }
 return(abs);
 }

 void filter(void)
 {
 uchar i=0,F_count=0,coeff=0;
 float Abs=0.00;

 //ȷ��һ���˲�ϵ��
 for(i=1;i<N;i++)
 {
 Abs=abs(Or_data[i-1],Or_data[i]);
 if(!(Dr1_flag^Dr0_flag)) //ǰ�����ݱ仯����һ��
 { 
 F_count++;
 if(Abs>=Thre_value) 
 {
 F_count++;
 F_count++;
 }
 if(F_count>=12)
 F_count=12;
 coeff=20*F_count; 
 }
 else //ȥ����
 coeff=5;
 //һ���˲��㷨
 if(Dr1_flag==0) //��ǰֵС��ǰһ��ֵ
 Or_data[i]=Or_data[i-1]-coeff*(Or_data[i-1]-Or_data[i])/256;
 else
 Or_data[i]=Or_data[i-1]+coeff*(Or_data[i]-Or_data[i-1])/256; 

 F_count=0; //�˲�����������
 Dr0_flag=Dr1_flag;
 }
 }

 9����Ȩ����ƽ���˲���

 /************************************************************
 coe:����Ϊ��Ȩϵ���������ڳ���洢����
 sum_coe:��Ȩϵ����
 ************************************************************/

 #define N 12

 const char code coe[N] = {1,2,3,4,5,6,7,8,9,10,11,12};
 const char code sum_coe = 1+2+3+4+5+6+7+8+9+10+11+12;

 unsigned char filter()
 {
 unsigned char i;
 unsigned char value_buf[N];
 int sum=0;

 for (i=0;i<N;i++)
 {
 value_buf[i] = get_ad();
 delay();
 }

 for (i=0,i<N;i++)
 {
 value_buf[i]=value_buf[i+1];
 sum += value_buf[i]*coe[i];
 }

 sum/=sum_coe;
 value=sum/N;
 return(value);
 }

 10�������˲���

 /************************************************

 *************************************************/
 #define N 12

 unsigned char filter()
 {
 unsigned char i=0;
 unsigned char new_value;
 new_value = get_ad();
 if(value !=new_value);
 {
 i++;
 if (i>N)
 {
 i=0;
 value=new_value;
 }
 }
 else i=0;
 return(value);
 
 
 ������������������������������������������
 ��ʵ����Щȫ������FIR LPF���ο��أ������˾���ֱ���ø�Biquad��IIR LPF��������С����
 