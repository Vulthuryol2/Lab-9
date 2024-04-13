#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType record;
	struct HashType *next;
};

// Compute the hash function
int hash(int x)
{
	return x % 31;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;
	struct HashType *node;

	for (i=0; i<31; ++i)
	{
		node = pHashArray[i].next;
		while (node != NULL)
		{
			printf("Index %d -> id: %d, name: %c, order: %d\n", i, node->record.id, node->record.name, node->record.order);
			node = node->next;
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	struct HashType *pHashArray;
	int recordSz = 0;
	int i, index;
	struct HashType *newNode;
	int hashSz = 31;
\
	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	pHashArray = (struct HashType*) malloc(sizeof(struct HashType) * 31);
	for (i = 0; i < 31; ++i)
	{
		pHashArray[i].next = NULL;
	}

	// Hash records
	for (i = 0; i < recordSz; ++i)
	{
		index = hash(pRecords[i].id);
		newNode = (struct HashType*) malloc(sizeof(struct HashType));
		newNode->record = pRecords[i];
		newNode->next = pHashArray[index].next;
		pHashArray[index].next = newNode;
	}

	displayRecordsInHash(pHashArray, 31);

	free(pRecords);
	free(pHashArray);

	return 0;
}