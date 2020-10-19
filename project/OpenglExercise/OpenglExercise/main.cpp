
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
namespace light_casters_directional{ int main(); }
namespace light_casters_point { int main(); }
namespace light_casters_spot { int main(); }
namespace light_casters_spot_soft { int main(); }
namespace multiple_lights { int main(); }
namespace model_loading { int main(); }
namespace model_loading_light { int main(); }

namespace depth_testing_view { int main(); }
namespace stencil_testing { int main(); }
namespace blending_discard { int main(); }
namespace blending_sorted { int main(); }

namespace cubemaps_skybox{int main();}
namespace cubemaps_environment_mapping { int main(); }
namespace framebuffers { int main(); }

int main()
{
	int ret = 0;
    //ret = colorTriangleProcess();
	//ret = textureProcess();
	//ret = transformProcess();
	//ret = coordinate_systems_depthProcess();
	//ret = cameraExerciseProcess();
	//ret = lightingColors::lightingColorsProcess();
	//ret = basic_lighting_specular::main();
	//ret = material::main();
	//ret = lighting_maps_diffuse::main();
	//ret = lighting_maps_specular::main();
	//ret = light_casters_directional::main();
	//ret = light_casters_point::main();
	//ret = light_casters_spot::main();
	//ret = light_casters_spot_soft::main();
	//ret = multiple_lights::main();
	//ret = model_loading::main();
	//ret = model_loading_light::main();

	//ret = depth_testing_view::main();
	//ret = stencil_testing::main();
	//ret = blending_discard::main();
	ret = blending_sorted::main();

	//ret = cubemaps_skybox::main();
	//ret = cubemaps_environment_mapping::main();
	//ret = framebuffers::main();
	return ret;
}

