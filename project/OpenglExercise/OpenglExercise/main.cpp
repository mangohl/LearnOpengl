
int windowProcess();
int triangleProcess();
int colorTriangleProcess();
int textureProcess();
int transformProcess();
int coordinate_systems_depthProcess();
int cameraExerciseProcess();

namespace lightingColors{int lightingColorsProcess();}
namespace basic_lighting_specular {int main();}
namespace material { int main(); }
namespace lighting_maps_diffuse { int main(); }
namespace lighting_maps_specular { int main(); }

int main()
{
	int ret = 0;
    // ret = triangleProcess();
	//ret = transformProcess();
	//ret = coordinate_systems_depthProcess();
	//ret = cameraExerciseProcess();
	//ret = lightingColors::lightingColorsProcess();
	//ret = basic_lighting_specular::main();
	//ret = material::main();
	//ret = lighting_maps_diffuse::main();
	ret = lighting_maps_specular::main();

	return ret;
}

