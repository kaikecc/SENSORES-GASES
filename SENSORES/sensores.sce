arq = uigetfile("*.txt","C:\Users\kaike\Desktop\","Escolha um arquivo .txt: ");

m = fscanfMat(arq);
mq135 = m(:,1);
mq7 = m(:,2);
mq8 = m(:,3);
mq3 = m(:,4);

t = 0.1:0.1:(length(m(:,1))*0.1);

clf()
subplot(221);
plot(t,m(:,1),'r')
xtitle("MQ-135")

subplot(222);
plot(t,mq7,'b')
xtitle("MQ-7")

subplot(223);
plot(t,mq8,'g')
xtitle("MQ-8")

subplot(224);
plot(t,mq3,'y')
xtitle("MQ-3")

xgrid
