////////////////////////////////////////////////////////////////////
// The car files are courtesy of Alex Segal found in gicp package //
////////////////////////////////////////////////////////////////////
#include "jafarConfig.h"

#include "jmath/jann.hpp"
#include "jmath/ublas_data_file.hpp"

int main(int argc, char** argv) {

#ifdef HAVE_FLANN
	using namespace jafar;
	using namespace std;
	using namespace jann;

	jmath::matrix_file<float> model;
	model.load("car0.ascii");
	for (unsigned int r = 0; r < model.data.size1(); r++) {
		for (unsigned int c = 0; c < model.data.size2(); c++)
			cout << model.data(r,c)<< " ";
		cout << endl;
	}
	jmath::matrix_file<float> scene;
	scene.load("car1.ascii");
	ublas::matrix<float> dists(scene.data.size1(), 10);
	ublas::matrix<int> indices(scene.data.size1(), 10);
	KD_tree_index< flann::L2<float> > tree(model.data);
	tree.build();
	tree.knn_search(scene.data, indices, dists, 10, search_params(32));

#else /* HAVE_FLANN */

	std::cout << "Please install the flann library to get this demo" << std::endl;

#endif /* HAVE_FLANN */

	return 0;
}
