/*
 * Eos - A 3D Morphable Model fitting library written in modern C++11/14.
 *
 * File: include/eos/morphablemodel/io/cvssp.hpp
 *
 * Copyright 2014, 2015 Patrik Huber
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#ifndef IO_CVSSP_HPP_
#define IO_CVSSP_HPP_

#include "eos/morphablemodel/MorphableModel.hpp"

#include "opencv2/core/core.hpp"

#ifdef WIN32
	#define BOOST_ALL_DYN_LINK	// Link against the dynamic boost lib. Seems to be necessary because we use /MD, i.e. link to the dynamic CRT.
	#define BOOST_ALL_NO_LIB	// Don't use the automatic library linking by boost with VS2010 (#pragma ...). Instead, we specify everything in cmake.
#endif
#include "boost/filesystem/path.hpp"

#include <vector>

namespace eos {
	namespace morphablemodel {

/**
 * Load a shape or color model from a .scm file containing
 * a Morphable Model in the Surrey format.
 *
 * Note on multi-resolution models: The landmarks to vertex-id mapping is
 * always the same. The lowest resolution model has all the landmarks defined
 * and for the higher resolutions, the mesh is divided from that on.
 * Note: For new landmarks we add, this might not be the case if we add them
 * in the highest resolution model, so take care!
 *
 * - The pcaBasis matrix stored in the file and loaded is the orthogonal PCA basis, i.e. it is not normalised by the eigenvalues.
 *
 * @param[in] modelFilename A binary .scm-file containing the model.
 * @param[in] isomapFile An optional path to an isomap containing texture coordinates.
 * @return The Morphable Model loaded from the file.
 */
MorphableModel loadScmModel(boost::filesystem::path modelFilename, boost::filesystem::path isomapFile = boost::filesystem::path());

/**
 * Load a set of 2D texture coordinates pre-generated by the isomap algorithm.
 * After loading, we rescale the coordinates to [0, 1] x [0, 1].
 *
 * @param[in] isomapFile Path to an isomap file containing texture coordinates.
 * @return The 2D texture coordinates for every vertex.
 */
std::vector<cv::Vec2f> loadIsomap(boost::filesystem::path isomapFile);

	} /* namespace morphablemodel */
} /* namespace eos */

#endif /* IO_CVSSP_HPP_ */
