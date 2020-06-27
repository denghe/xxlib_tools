#pragma once
#include "Pathway_class_lite.h"

// 2 控制点的贝塞尔( p c c p c c p ... ) 切片转点
inline void BezierToPoints(std::vector<Pathway::Point>& ps, std::vector<Pathway::Point> const& bs) {
	auto len = (bs.size() - 1) / 3;
	size_t totalSegments = 0;
	for (size_t j = 0; j < len; ++j) {
		totalSegments += bs[j * 3].numSegments;
	}
	ps.resize(totalSegments);
	totalSegments = 0;
	for (size_t j = 0; j < len; ++j) {
		auto idx = j * 3;
		auto numSegments = bs[idx].numSegments;
		auto step = 1.0f / numSegments;
		for (size_t i = 0; i < numSegments; ++i) {
			auto t = step * i;
			auto t1 = 1 - t;
			ps[totalSegments + i] = bs[idx] * t1 * t1 * t1
				+ bs[idx + 1] * 3 * t * t1 * t1
				+ bs[idx + 2] * 3 * t * t * (1 - t)
				+ bs[idx + 3] * t * t * t;
		}
		totalSegments += numSegments;
	}
}

// 途径点曲线( p p p ... ) 转 2 控制点的贝塞尔( p c c p c c p ... )
inline void CurveToBezier(std::vector<Pathway::Point>& bs, std::vector<Pathway::Point> const& cs) {
	auto n = cs.size();
	auto len = n * 3 - 2;
	bs.resize(len);

	bs[0] = cs[0];
	bs[1] = (cs[1] - cs[0]) * cs[0].tension + cs[0];

	for (size_t i = 0; i < n - 2; i++) {
		auto diff = (cs[i + 2] - cs[i]) * cs[i].tension;
		bs[3 * i + 2] = cs[i + 1] - diff;
		bs[3 * i + 3] = cs[i + 1];
		bs[3 * i + 4] = cs[i + 1] + diff;
	}
	bs[len - 2] = (cs[n - 2] - cs[n - 1]) * cs[n - 2].tension + cs[n - 1];
	bs[len - 1] = cs[n - 1];
}

// todo: 循环线 前后加点&切割
