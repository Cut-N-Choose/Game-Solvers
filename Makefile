
all: MajorityCut SingleCut BatchedCut
	
MajorityCut: test/test_MajorityCut.c MajorityCut/MajorityCut.c MajorityCut/MCLPS.c 
	gcc test/test_MajorityCut.c MajorityCut/MajorityCut.c MajorityCut/MCLPS.c -o bin/MajorityCut

SingleCut: SingleCut/SingleCut.c test/test_SingleCut.c
	gcc test/test_SingleCut.c  SingleCut/SingleCut.c  -o bin/SingleCut

BatchedCut: BatchedCut/BatchedCut.c  BatchedCut/BCGFC.c test/test_BatchedCut.c
	gcc test/test_BatchedCut.c BatchedCut/BatchedCut.c BatchedCut/BCGFC.c  -o bin/BatchedCut


