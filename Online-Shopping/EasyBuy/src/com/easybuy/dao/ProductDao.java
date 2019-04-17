package com.easybuy.dao;

import com.easybuy.entity.Product;

import java.util.List;

public interface ProductDao {

    Integer add (Product product) throws Exception;

    Integer update(Product product) throws Exception;

    Integer updateStock(Integer id, Integer quantity) throws Exception;

    Integer deleteProductById(Integer id) throws Exception;

    Product getProductById(Integer id) throws Exception;

    Integer queryProductCount(String proName, Integer categoryId, Integer level) throws Exception;


    List<Product> getProductList(Integer currentPageNo, Integer pageSize, String proName, Integer categoryId, Integer level) throws Exception;
}
