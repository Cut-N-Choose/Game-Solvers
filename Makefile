
all: MajorityCut SingleCut BatchedCut
	
MajorityCut: MajorityCut.c MCLPS.c test_MajorityCut.c
	gcc test_MajorityCut.c MajorityCut.c MCLPS.c -o MajorityCut

SingleCut: SingleCut.c test_SingleCut.c
	gcc test_SingleCut.c  SingleCut.c  -o SingleCut

BatchedCut: BatchedCut.c BCGFC.c test_BatchedCut.c
	gcc test_BatchedCut.c BatchedCut.c BCGFC.c  -o BatchedCut


