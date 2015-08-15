spfa
1. 判断有向图负环只需判一个点是否入队N次，此时可能图不连通，就要先把所有点入队
2. SLF：Small Label First 设要加入的节点是j，队首元素为i，若dist(j)<dist(i)，则将j插入队首，否则插入队尾。 
3. LLL：Large Label Last 策略，设队首元素为i，队列中所有dist值的平均值为x，若dist(i)>x则将i插入到队尾，查找下一元素，直到找到某一i使得dist(i)<=x，则将i出对进行松弛操作


2-sat

//输出方案，即反向连边后拓扑排序，扫到未染色的顶染红，对立点及其能到的点染蓝
void dye(int x)
{
    col[x] = 2;
    for (int p = fir2[x]; p; p = nxt2[p])
	if (!col[e2[p]])
	    dye(e2[p]);
}

void twoSet()
{
	now = cnt = 0;
	slack.clear();
	mem(dfn);
	mem(popS);
	mem(inD);
	REPP(i, 1, 2 * n)
	    if (!dfn[i])
		tarjan(i);
	int ok = 1;
	REPP(i, 1, n)
	    if (belong[i] == belong[i + n])
	    {ok = 0; break;}
	if (!ok)
	{
	    printf("No solution.\n");
	    return ;
	}
	num = 0;
	mem(fir2); //不要用fir，fir1,容易打错又编译不会出错
	REPP(i, 1, 2 * n)
	    for (int p = fir1[i]; p; p = nxt1[p])
		if (belong[i] != belong[e1[p]])
		    link2(belong[e1[p]], belong[i]);
	REPP(i, 1, 2 * n)
	    cont[belong[i]] = belong[getCont(i)]; //相应的反点也一定要改变
	topSort();
	mem(col);
	REPP(i, 1, cnt)
	    if (!col[top[i]])
	    {
			col[top[i]] = 1;
			dye(cont[top[i]]);
	    }
	REPP(i, 1, n)
	    if (col[belong[i]] == 1)
			printf("A\n");
	    else printf("B\n");
}
return 0;
}
