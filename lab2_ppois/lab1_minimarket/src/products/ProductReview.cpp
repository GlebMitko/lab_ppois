#include "../../include/products/ProductReview.hpp"

namespace minimarket {
namespace products {

ProductReview::ProductReview(const std::string& id, const std::string& prodId, int rate, const std::string& cmt)
    : reviewId(id), productId(prodId), rating(rate), comment(cmt) {}

bool ProductReview::validateRating() const {
    return rating >= 1 && rating <= 5;
}

double ProductReview::calculateReviewImpact() const {
    return rating * 0.2;
}

std::string ProductReview::generateSummary() const {
    return "Rating: " + std::to_string(rating) + "/5 - " + comment.substr(0, 50) + "...";
}

} // namespace products
} // namespace minimarket
