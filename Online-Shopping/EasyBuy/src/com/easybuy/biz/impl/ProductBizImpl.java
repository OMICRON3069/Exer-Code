package com.easybuy.biz.impl;

import com.easybuy.biz.ProductBiz;
import com.easybuy.dao.ProductDao;
import com.easybuy.dao.impl.ProductDaoImpl;
import com.easybuy.entity.Product;
import com.easybuy.util.DataSourceUtil;

import java.sql.Connection;
import java.util.List;

public class ProductBizImpl implements ProductBiz {
    @Override
    public boolean add(Product product) {
        Connection connection = null;

        Integer cc = 0;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            cc= productDao.add(product);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public boolean update(Product product) {
        Connection connection = null;

        Integer cc = 0;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            cc= productDao.update(product);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public boolean updateStock(Integer productId, Integer stock) {
        Connection connection = null;

        Integer cc = 0;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            cc= productDao.updateStock(productId,stock);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public boolean deleteProductById(Integer productId) {
        Connection connection = null;

        Integer cc = 0;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            cc= productDao.deleteProductById(productId);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc > 0;
    }

    @Override
    public Product getProductById(Integer productId) {
        Connection connection = null;

        Product  product = null;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            product= productDao.getProductById(productId);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return product;
    }

    @Override
    public Integer queryProductCount(String proName, Integer categoryId, Integer level) {
        Connection connection = null;

        Integer cc = 0;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            cc= productDao.queryProductCount(proName,categoryId,level);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return cc ;
    }

    @Override
    public List<Product> getProductList(Integer currentPageNo, Integer pageSize, String proName, Integer categoryId, Integer level) {
        Connection connection = null;

        List<Product> productList = null;
        try {
            connection = DataSourceUtil.openConnection();

            ProductDao productDao = new ProductDaoImpl(connection);

            productList= productDao.getProductList(currentPageNo,pageSize,proName,categoryId,level);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }
        return productList;
    }
}
