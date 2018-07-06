package com.easybuy.biz.impl;

import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.dao.ProductCategoryDao;
import com.easybuy.dao.impl.ProductCategoryDaoImpl;
import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.ProductCategoryVo;

import java.sql.Connection;
import java.util.List;

public class ProductCategoryBizImpl implements ProductCategoryBiz {
    @Override
    public void addProductCategory(ProductCategory productCategory) {
        Connection connection = null;

        try {
            connection = DataSourceUtil.openConnection();
            ProductCategoryDao dao = new ProductCategoryDaoImpl(connection);
            dao.add(productCategory);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
    }

    @Override
    public void updateProductCategory(ProductCategory productCategory) {
        Connection connection = null;

        try {
            connection = DataSourceUtil.openConnection();
            ProductCategoryDao dao = new ProductCategoryDaoImpl(connection);
            dao.update(productCategory);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
    }

    @Override
    public void deleteById(Integer id) {
        Connection connection = null;

        try {
            connection = DataSourceUtil.openConnection();
            ProductCategoryDao dao = new ProductCategoryDaoImpl(connection);
            dao.deleteById(id);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
    }

    @Override
    public Integer Count(ProductCategoryParam param) {
        Connection connection = null;

        Integer cc = 0;

        try {
            connection = DataSourceUtil.openConnection();
            ProductCategoryDao dao = new ProductCategoryDaoImpl(connection);
            cc = dao.count(param);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc;
    }

    @Override
    public ProductCategory ProductCategoryById(Integer id) {
        Connection connection = null;

        ProductCategory productCategory = null;

        try {
            connection = DataSourceUtil.openConnection();
            ProductCategoryDao dao = new ProductCategoryDaoImpl(connection);
            productCategory = dao.ProductCategoryById(id);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return productCategory;
    }

    @Override
    public List<ProductCategory> ProductCategoryList(ProductCategoryParam param) {
        Connection connection = null;

        List<ProductCategory> productCategoryList = null;

        try {
            connection = DataSourceUtil.openConnection();
            ProductCategoryDao dao = new ProductCategoryDaoImpl(connection);
            productCategoryList = dao.ProductCategoryList(param);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return productCategoryList;
    }

    @Override
    public List<ProductCategoryVo> AllProductCategoryList() {
        return null;
    }
}
