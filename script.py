
from subprocess import call
# i:mean j:threads k:doing 10 times to get average value
results=[0]*10
f = open('graph', 'w')
i=1
while (i<=100):
    j=2
    while (j < 17):
        for k in range(10):
            call(["./trc",str(j),"1000",str(i)])
	    data=open("results").readline().rstrip()
            results[k]=data
	print results
	total=sum(int(temp) for temp in results)
	avg=total/10
	print avg
	throughput=(j*1000)/(avg*1.0)
	f.write('For'+str(j)+'threads,with mean: '+str(i)+'average time is'+ str(avg)+'\n')
	f.write('Throughput is'+str(throughput)+'\n\n')
        results=[0]*10
        j<<1
    if i==1:
        i=10
    else:
        i+=10

f.close()


