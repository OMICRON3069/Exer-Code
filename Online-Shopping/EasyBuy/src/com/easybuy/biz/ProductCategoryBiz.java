package com.easybuy.biz;

import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;
import com.easybuy.util.ProductCategoryVo;

import java.util.List;

public interface ProductCategoryBiz {
    void addProductCategory(ProductCategory productCategory);

    void updateProductCategory(ProductCategory productCategory);

    void deleteById(Integer id);

    Integer Count(ProductCategoryParam param);

    ProductCategory ProductCategoryById(Integer id);

    List<ProductCategory> ProductCategoryList(ProductCategoryParam param);

    List<ProductCategoryVo> AllProductCategoryList();
}
