float wskNaFunkcje(float a,float b,float(*funkcja)(float,float)){
return(funkcja(a,b));
}
float suma(float a, float b){
return (a+b);
}
float iloczyn(float a, float b){
return (a*b);
}
float iloraz(float a,float b){
if(a!=0){
return (a/b);
}
else{
return 1;
}
}
float roznica(float a,float b){
return (a-b);
}
