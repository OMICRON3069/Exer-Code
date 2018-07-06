package com.easybuy.biz.impl;

import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.dao.ProductCategoryDao;
import com.easybuy.dao.impl.ProductCategoryDaoImpl;
import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.ProductCategoryVo;

import java.sql.Connection;
import java.util.ArrayList;
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

        List<ProductCategoryVo> productCategoryVo1List = new ArrayList<ProductCategoryVo>();

        List<ProductCategory> productCategory1List = getProductCategories(null);

        for (ProductCategory product1Category:productCategory1List) {
            ProductCategoryVo productCategoryVo1 = new ProductCategoryVo();
            productCategoryVo1.setProductCategory(product1Category);
            List<ProductCategoryVo> productCategoryVo1ChildList = new ArrayList<ProductCategoryVo>();
            List<ProductCategory> productCategory2List = getProductCategories(product1Category.getId());


            //2
            for (ProductCategory product2Category:productCategory2List) {
                ProductCategoryVo productCategoryVo2 = new ProductCategoryVo();
                productCategoryVo1ChildList.add(productCategoryVo2);
                productCategoryVo2.setProductCategory(product2Category);

                //3
                List<ProductCategoryVo> productCategoryVo2ChildList = new ArrayList<ProductCategoryVo>();
                productCategoryVo2.setProductCategoryVoList(productCategoryVo2ChildList);
                List<ProductCategory> productCategory3List = getProductCategories(product2Category.getId());
                for (ProductCategory product3Category: productCategory3List) {
                    ProductCategoryVo productCategoryVo3 = new ProductCategoryVo();
                    productCategoryVo3.setProductCategory(product3Category);
                    productCategoryVo2ChildList.add(productCategoryVo3);
                }

            }

            productCategoryVo1.setProductCategoryVoList(productCategoryVo1ChildList);
            productCategoryVo1List.add(productCategoryVo1);
        }

        return productCategoryVo1List;
    }

    private List<ProductCategory> getProductCategories(Integer parentId) {

        Connection connection = null;

        List<ProductCategory> productCategoryList = null;

        try {
            connection = DataSourceUtil.openConnection();

            ProductCategoryDao productCategoryDao = new ProductCategoryDaoImpl(connection);

            ProductCategoryParam param = new ProductCategoryParam();

            if (EmptyUtils.isNotEmpty(parentId)) {
                param.setParentId(parentId);
            }
            else {
                param.setParentId(0);
            }
            productCategoryList = productCategoryDao.ProductCategoryList(param);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            DataSourceUtil.closeConnection(connection);
        }

        return productCategoryList;
    }
}
