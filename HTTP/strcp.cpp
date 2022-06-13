void strcp(char *out, char *in, int size){
	for(int i=0; i<size; i++)
		out[i] = in[i];
	out[size] = 0;
	return;
}
