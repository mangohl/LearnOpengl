
int windowProcess();
int triangleProcess();
int colorTriangleProcess();
int textureProcess();
int transformProcess();
int coordinate_systems_depthProcess();

int main()
{
	int ret = 0;
    // ret = triangleProcess();
	//ret = transformProcess();
	ret = coordinate_systems_depthProcess();

	return ret;
}

