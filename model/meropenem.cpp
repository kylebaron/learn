[PROB]
Meropenem PopPK

https://www.ncbi.nlm.nih.gov/pubmed/16988206

[SET] delta=0.1, end=8, req=""

[PKMODEL] cmt = "CENT, PERIPH"  

[PARAM] @annotated
WT   : 70 : Weight (kg)
CLCR : 83 : Creatinine clearance (ml/min)
AGE  : 35 : Age (years)
 
[THETA] @annotated
 1.50E+01 : Typical value of clearance (L/h)
 1.27E+01 : Typical value of volume 1 (L)
 1.52E+01 : Intercompartmental clearance (L/h) 
 1.24E+01 : Typical value of volume 2 (L) 
-4.47E-01 : AGE on CL
 8.20E-01 : WT on V1
 1.88E-01 : Proportional error standard deviation
 4.76E-01 : Additive error standard deviation
 6.20E-01 : CLCR on CL 

[MAIN]

double TVCL     = THETA1;
double TVV1     = THETA2;
double TVQ      = THETA3;
double TVV2     = THETA4;
double CL_AGE   = THETA5;
double V1_WT    = THETA6;
double RUV_PROP = THETA7;
double RUV_ADD  = THETA8;
double CL_CLCR  = THETA9;

double LOGTWT = log((WT/70.0)); 
  
double LOGTAGE = log((AGE/35.0));
  
double LOGTCLCR = log((CLCR/83.0));
  
double CL =  exp(log(TVCL) + CL_AGE * LOGTAGE + CL_CLCR * LOGTCLCR +  ETA(1)) ;

double V1 =  exp(log(TVV1) + V1_WT * LOGTWT +  ETA(2)) ;

double Q  =  exp(log(TVQ) +  ETA(3)) ;

double V2 =  exp(log(TVV2 +  ETA(4));

[OMEGA] @annotated
ECL : 8.84E-02 : ETA on CL
EV1 : 9.76E-02 : ETA on V1
EQ  : 1.03E-01 : ETA on Q
EV2 : 7.26E-02 : ETA on V2

[SIGMA] @annotated
EP : 1 : Not used

[TABLE] 
capture CC = (CENT/V1);
double IPRED = CC;
double W = sqrt((RUV_ADD*RUV_ADD)+ (RUV_PROP*RUV_PROP*IPRED*IPRED));
capture Y = IPRED+W*EPS(1);
