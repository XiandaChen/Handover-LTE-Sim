awk 'BEGIN { ho=0; TIME=75; }
	{
	if ($1=="SUCCESSFUL_HANDOVER") { ho=ho+1; }
	}
END	{ printf "4.5f\n", ho/TIME }' $1
