package com.easybuy.dao;

import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;

import java.util.List;

public interface ProductCategoryDao  {
    Integer add (ProductCategory productCategory);

    Integer update(ProductCategory productCategory);

    void deleteById(Integer id);

    Integer count(ProductCategoryParam param);

    ProductCategory ProductCategoryById(Integer id);

    List<ProductCategory> ProductCategoryList(ProductCategoryParam param);
}
