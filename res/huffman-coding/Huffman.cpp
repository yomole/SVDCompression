#include "Huffman.h"

//Compresses File using Huffman Coding
void compressFile(const char* path,const char* output_path, map<unsigned char, string>& codes)
{
	int sz = 0;
	int paddedBits = 0;
	map<unsigned char, int> freqtable;
	unsigned char* buffer = readFileIntoBuffer(path, sz);
	for (int i = 0; i < sz; i++)
	{
		freqtable[buffer[i]]++;
	}
	Tree* root = buildHuffmanTree(convertToVector(freqtable));
	traverseHuffmanTree(root, "", "", codes);
	string outputString = getHuffmanBitstring(buffer, codes, sz, paddedBits);
	sz = outputString.size();
	vector<unsigned char> outputBufferV;
	getBufferFromString(outputString, outputBufferV, sz);
	unsigned char* outputBuffer = outputBufferV.data();
	writeHeader(output_path, codes, paddedBits);
	writeFileFromBuffer(output_path, outputBuffer, sz, 1);
}

//Writes buffer file for an image
void writeFileFromBuffer(const char* path, unsigned char* buffer, int sz, int flag)
{
    FILE* fp;
    if (flag == 0)
    {
        fopen_s(&fp,path, "wb");
    }

    else {
        fopen_s(&fp, path, "ab");
    }
    //write buffer files
    fwrite(buffer, 1, sz, fp);

    fclose(fp);
}


void writeHeader(const char* path, map<unsigned char, string> codes, int paddedBits) {

    int size = codes.size();
    writeFileFromBuffer(path, (unsigned char*)&paddedBits, sizeof(int), 0);
    writeFileFromBuffer(path, (unsigned char*)&size, sizeof(int), 1);
    char nullBit = '\0';
    for (map<unsigned char, string>::iterator i = codes.begin(); i != codes.end(); i++)
    {
        writeFileFromBuffer(path, (unsigned char*)&i->first, 1, 1);
        int len = i->second.size();
        writeFileFromBuffer(path, (unsigned char*)&len, sizeof(int), 1);
        writeFileFromBuffer(path, (unsigned char*)i->second.c_str(), i->second.size(), 1);
    }
}

//Builds Huffman Tree and sends in a freqTable with values
Tree* buildHuffmanTree(vector<pair<unsigned char, int> > freqTable)
{
    priority_queue<Tree*, vector<Tree*>, Huffman> huffQueue;
    for (int i = 0; i < freqTable.size(); i++)
    {
        Tree* node = new Tree();
        node->frequency = freqTable[i].second;
        node->character = freqTable[i].first;

        huffQueue.push(node);
    }
    while (huffQueue.size() > 1)
    {
        Tree* a, * b;
        a = huffQueue.top();
        huffQueue.pop();

        b = huffQueue.top();
        huffQueue.pop();
        Tree* c = new Tree();
        c->frequency = a->frequency + b->frequency;
        c->left = a;
        c->right = b;
        huffQueue.push(c);
    }
    return huffQueue.top();
}

//Converts char to binary
string toBinary(unsigned  char a){
    string output = "";
    while (a != 0)
    {
        string bit = a % 2 == 0 ? "0" : "1";
        output += bit;
        a /= 2;
    }

    if (output.size() < 8)
    {
        int deficit = 8 - output.size();
        for (int i = 0; i < deficit; i++)
        {
            output += "0";
        }
    }

    reverse(output.begin(), output.end());
    return output;

}

void traverseHuffmanTree(Tree* root, string prev, string toAppend, map<unsigned char, string> codemap)
{

    prev += toAppend;

    if (root->right == NULL && root->left == NULL)
    {
        codemap[root->character] = prev;
    }
    if (root->right != NULL)
    {
        traverseHuffmanTree(root->right, prev, "1", codemap);
    }

    if (root->left != NULL)
    {
        traverseHuffmanTree(root->left, prev, "0", codemap);
    }
}

vector<pair<unsigned char, int> > convertToVector(map<unsigned char, int> codes)
{
    vector<pair<unsigned char, int> > codesV;

    for (map<unsigned char, int>::iterator i = codes.begin(); i != codes.end(); i++)
    {
        codesV.push_back(make_pair(i->first, i->second));
    }

    return codesV;
}

string getHuffmanBitstring(unsigned char* buffer, map<unsigned char, string> codes, int sz, int& paddedBits)
{
    string outputBuffer = "";
    for (int i = 0; i < sz; i++)
    {
        outputBuffer = outputBuffer + codes[buffer[i]];
    }

    if (outputBuffer.size() % 8 != 0)
    {
        int deficit = 8 * ((outputBuffer.size() / 8) + 1) - outputBuffer.size();
        paddedBits = deficit;
        for (int i = 0; i < deficit; i++)
        {
            outputBuffer += "0";
        }
    }


    return outputBuffer;

}

unsigned char* getBufferFromString(string bitstring, vector<unsigned char>& outputBuffer, int& sz)
{
    int interval = 0;
    unsigned char bit = 0;

    for (int i = 0; i < sz; i++)
    {
        bit = (bit << 1) | (bitstring[i] - '0');

        interval++;
        if (interval == 8)
        {
            interval = 0;
            outputBuffer.push_back(bit);
            bit = 0;

        }
    }
    sz = outputBuffer.size();
    return outputBuffer.data();
}

string getStringFromBuffer(unsigned char* buffer, int sz)
{
    string bitstring = "";
    for (int i = 0; i < sz; i++)
    {
        bitstring += toBinary(buffer[i]);
    }

    return bitstring;
}

unsigned char* getDecodedBuffer(string bitstring, vector<unsigned char>& buffer, map<unsigned char, string> codes, int& sz, int paddedBits)
{
    string bit = "";
    map<string, unsigned char> reversecodes;

    for (map<unsigned char, string>::iterator i = codes.begin(); i != codes.end(); i++)
    {
        reversecodes[i->second] = i->first;
    }

    for (int i = 0; i < bitstring.size() - paddedBits; i++)
    {
        bit += string(1, bitstring[i]);
        if (reversecodes.find(bit) != reversecodes.end())
        {
            buffer.push_back(reversecodes[bit]);
            bit = "";
        }
    }

    sz = buffer.size();
    return buffer.data();
}

unsigned char* readHeader(unsigned char* buffer, map<unsigned char, string>& codes, int& paddedBits, int& sz)
{
    paddedBits = *((int*)buffer);
    //cout << paddedBits << "PADDED" << endl;
    buffer = buffer + 4;
    sz -= 4;
    int size = *((int*)buffer);
    buffer = buffer + 4;
    sz -= 4;
    for (int i = 0; i < size; i++)
    {
        unsigned char key = buffer[0];
        buffer++;
        sz--;
        int len = *((int*)buffer);
        buffer += 4;
        sz -= 4;
        char* value = (char*)malloc(len + 1);

        for (int j = 0; j < len; j++)
        {
            value[j] = buffer[j];
        }
        buffer += len;
        sz -= len;
        value[len] = '\0';
        codes[key] = value;
    }

    return buffer;
}


void decompressFile(const char* inputPath, const char* outputPath)
{
    int sz = 0;
    map<unsigned char, string> codes;
    int paddedBits = 0;
    unsigned char* fileBuffer = readFileIntoBuffer(inputPath, sz);
    fileBuffer = readHeader(fileBuffer, codes, paddedBits, sz);
    string fileBitString = getStringFromBuffer(fileBuffer, sz);
    vector<unsigned char> outputBufferV;
    unsigned char* outputBuffer;
    getDecodedBuffer(fileBitString, outputBufferV, codes, sz, paddedBits);
    outputBuffer = outputBufferV.data();
    writeFileFromBuffer(outputPath, outputBuffer, sz, 0);
}

//Compares both files compressed and uncompressed (the difference should be 0 since there is nothing lost during compression )
int CompareFiles(const char* pFname1,const char* pFname2)
{
    FILE* pFile1, * pFile2;
    long      lSize1, lSize2;
    int       i = 0;
    char      tmp1, tmp2;

    pFile1 = fopen(pFname1, "r");
    pFile2 = fopen(pFname2, "r");

    fseek(pFile1, 0, SEEK_END);
    lSize1 = ftell(pFile1);
    rewind(pFile1);

    fseek(pFile2, 0, SEEK_END);
    lSize2 = ftell(pFile2);
    rewind(pFile2);

    if (lSize1 != lSize2) {
        printf("File sizes differ, %d vs. %d\n", lSize1, lSize2);
        return -1;
    }
    for (i = 0; i < lSize1; i++) {
        fread(&tmp1, 1, 1, pFile1);
        fread(&tmp2, 1, 1, pFile2);
        if (tmp1 != tmp2) {
            printf("%x: tmp1 0x%x != tmp2 0x%x\n", i, tmp1, tmp2);
            return -1;
        }
    }
    return 0;
}

unsigned char* readFileIntoBuffer(const char* path, int& sz)
{
    FILE* fp;
    fopen_s(&fp,path, "rb");
    if (fp == NULL)
    {
        cout << "File not found!" << endl;
        exit(-1);
    }
    sz = 0;
    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    unsigned char* buffer = (unsigned char*)malloc(sz);
    fread(buffer, 1, sz, fp);
    return buffer;
}
