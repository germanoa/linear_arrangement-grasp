for i in `ls -1 *.dat`; do
	glpsol --tmlim 3600 -m minla.mod -d $i -o $i.sol
done
