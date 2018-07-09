package com.easybuy.dao.impl;

import com.easybuy.dao.ProductDao;
import com.easybuy.entity.Product;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ProductDaoImpl extends BaseDaoImpl implements ProductDao {
    public ProductDaoImpl(Connection connection) {
        super(connection);
    }

    public static void main(String[] args) {
        ProductDaoImpl jibai = new ProductDaoImpl(DataSourceUtil.openConnection());

        Product p = new Product();

        /*
        p.setName("ganjibai11111");
        p.setDescription("jibai2");
        p.setStock(10);
        p.setPrice((float) 8848);
        p.setFileName("jibai3");
        p.setCategoryLevel1(1);
        p.setCategoryLevel2(2);
        p.setCategoryLevel3(3);
        //p.setId(1);


        if (jibai.deleteProductById(2) > 0) {
            System.out.println("Success");
        }
        else {
            System.out.println("Fail");
        }
        */

        //System.out.println(jibai.queryProductCount(null,null,null));

        List<Product> biu = jibai.getProductList(1, 1000, null, null, null);


        for (Product test : biu) {
            System.out.println(test.getId() + " " + test.getName());
        }
    }

    @Override
    public Integer add(Product product) {

        Integer cc = 0;

        String sql = " insert into easybuy_product (name, description, price, stock, categoryLevel1, " +
                " categoryLevel2, categoryLevel3, fileName, isDelete) values (?,?,?,?,?,?,?,?,?) ";

        Object[] params = {product.getName(), product.getDescription(), product.getPrice(),
                product.getStock(), product.getCategoryLevel1(), product.getCategoryLevel2(),
                product.getCategoryLevel3(), product.getFileName(), 0};

        try {
            cc = this.executeInsert(sql, params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return cc;
    }

    @Override
    public Integer update(Product product) {

        Integer id = 0;

        String sql = " update easybuy_product set name = ?, fileName = ?, categoryLevel1 = ?, " +
                "  categoryLevel2 = ?, categoryLevel3 = ? where id = ? ";

        Object[] params = {product.getName(), product.getFileName(), product.getCategoryLevel1(),
                product.getCategoryLevel2(), product.getCategoryLevel3(), product.getId()};

        try {
            id = this.executeUpdate(sql, params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return id;
    }

    @Override
    public Integer updateStock(Integer id, Integer quantity) {
        Integer cc = 0;

        String sql = " update easybuy_product set stock = ? where id = ? ";

        Object[] params = {quantity, id};

        try {
            cc = this.executeUpdate(sql, params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return cc;
    }

    @Override
    public Integer deleteProductById(Integer id) {
        Integer cc = 0;

        String sql = " delete from  easybuy_product  where id = ? ";

        Object[] params = {id};

        try {
            cc = this.executeUpdate(sql, params);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
        }

        return cc;
    }

    @Override
    public Product getProductById(Integer id) {

        Product pp = new Product();

        String sql = " select * from easybuy_product where id = ? ";

        Object[] params = {id};

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql, params);

            while (resultSet.next()) {
                pp = table2Class(resultSet);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return pp;
    }

    @Override
    public Integer queryProductCount(String proName,
                                     Integer categoryId, Integer level) {

        Integer cc = 0;

        StringBuffer sql = new StringBuffer(" select * from easybuy_product where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(proName)) {
            sql.append(" and name like ? ");
            paramList.add("%" + proName + "%");
        }

        if (EmptyUtils.isNotEmpty(categoryId)) {
            sql.append(" and (categoryLevel1 = ? or categoryLevel2 = ? or categoryLevel3 = ?) ");
            paramList.add(categoryId);
            paramList.add(categoryId);
            paramList.add(categoryId);
        }

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql.toString(), paramList.toArray());

            while (resultSet.next()) {
                cc = resultSet.getRow();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return cc;
    }

    @Override
    public List<Product> getProductList(Integer currentPageNo, Integer pageSize,
                                        String proName, Integer categoryId,
                                        Integer level) {

        List<Product> productList = new ArrayList<Product>();

        StringBuffer sql = new StringBuffer(" select * from easybuy_product where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(proName)) {
            sql.append(" and name like ? ");
            paramList.add("%" + proName + "%");
        }
        if (EmptyUtils.isNotEmpty(categoryId)) {
            sql.append(" and (categoryLevel1 = ? or categoryLevel2 = ? or categoryLevel3 = ?) ");
            paramList.add(categoryId);
            paramList.add(categoryId);
            paramList.add(categoryId);
        }

        Integer total = this.queryProductCount(proName, categoryId, level);

        Pager page = new Pager(total, pageSize, currentPageNo);

        sql.append(" limit  " + (page.getCurrentPage() - 1) * page.getRowPerpage() + " , " + page.getRowPerpage());

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql.toString(), paramList.toArray());

            while (resultSet.next()) {
                Product nigga = this.table2Class(resultSet);
                productList.add(nigga);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return productList;
    }

    @Override
    public Product table2Class(ResultSet rs) throws Exception {

        Product pp = new Product();

        pp.setId(rs.getInt("id"));
        pp.setName(rs.getString("name"));
        pp.setDescription(rs.getString("description"));
        pp.setPrice(rs.getFloat("price"));
        pp.setStock(rs.getInt("stock"));
        pp.setCategoryLevel1(rs.getInt("categoryLevel1"));
        pp.setCategoryLevel2(rs.getInt("categoryLevel2"));
        pp.setCategoryLevel3(rs.getInt("categoryLevel3"));
        pp.setFileName(rs.getString("fileName"));

        return pp;
    }
}
