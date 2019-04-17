package com.easybuy.biz;

import com.easybuy.entity.Product;

import java.util.List;

public interface ProductBiz {
    boolean add(Product product);

    boolean update(Product product);

    boolean updateStock(Integer productId, Integer stock);

    boolean deleteProductById(Integer productId);

    Product getProductById(Integer productId);

    Integer queryProductCount(String proName, Integer categoryId, Integer level);


    List<Product> getProductList(Integer currentPageNo, Integer pageSize,
                                 String proName, Integer categoryId, Integer level);

}
