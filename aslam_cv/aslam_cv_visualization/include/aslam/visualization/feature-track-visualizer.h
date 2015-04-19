#ifndef VISUALIZATION_FEATURE_TRACK_VISUALIZER_H_
#define VISUALIZATION_FEATURE_TRACK_VISUALIZER_H_

#include <aslam/common/memory.h>
#include <aslam/frames/feature-track.h>
#include <aslam/frames/visual-frame.h>
#include <opencv2/core/core.hpp>
#include <Eigen/Dense>

namespace aslam_cv_visualization {

/// Visualization for aslam::FeatureTracks.
class FeatureTrackVisualizer {
 public:
  FeatureTrackVisualizer() {rng_ = cv::RNG(0xFFFFFFFF);}

  void drawContinuousFeatureTracks(
      const aslam::VisualFrame::ConstPtr& frame,
      const aslam::FeatureTracks& terminated_feature_tracks,
      cv::Mat* image);

 private:
  typedef aslam::AlignedUnorderedMap<int, size_t>::type TrackIdToIndexMap;

  void preprocessLastFrame(TrackIdToIndexMap* track_id_to_keypoint_index_map);

  struct Track {
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    aslam::Aligned<std::vector, Eigen::Vector2d>::type keypoints;
    cv::Scalar color;
  };
  typedef aslam::AlignedUnorderedMap<int, Track>::type TrackMap;
  TrackMap track_id_to_track_map_;

  aslam::VisualFrame::ConstPtr last_frame_;

  cv::RNG rng_;
};
}  // namespace aslam_cv_visualization
#endif  // VISUALIZATION_FEATURE_TRACK_VISUALIZER_H_