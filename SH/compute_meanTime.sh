# meanTime between HOs, in ms
awk ' BEGIN {first=0; next=0; interval=0; number=0; }
	{
	{next=$1; number+=1; interval+=(next-first); first=next;}
	}
	END {printf "%4.5f\n", (interval/number)*1000}' $1
