
int windowProcess();
int triangleProcess();
int colorTriangleProcess();
int textureProcess();
int transformProcess();
int coordinate_systems_depthProcess();
int cameraExerciseProcess();

int main()
{
	int ret = 0;
    // ret = triangleProcess();
	//ret = transformProcess();
	//ret = coordinate_systems_depthProcess();
	ret = cameraExerciseProcess();

	return ret;
}

