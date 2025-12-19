#ifndef MINIMARKET_PRODUCTS_PRODUCTREVIEW_HPP
#define MINIMARKET_PRODUCTS_PRODUCTREVIEW_HPP

#include <string>

namespace minimarket {
namespace products {

class ProductReview {
public:
    ProductReview(const std::string& id, const std::string& prodId, int rate, const std::string& cmt);
    bool validateRating() const;
    double calculateReviewImpact() const;
    std::string generateSummary() const;

    const std::string& getReviewId() const { return reviewId; }
    const std::string& getProductId() const { return productId; }
    int getRating() const { return rating; }
    const std::string& getComment() const { return comment; }

private:
    std::string reviewId;
    std::string productId;
    int rating;
    std::string comment;
};

} // namespace products
} // namespace minimarket

#endif
