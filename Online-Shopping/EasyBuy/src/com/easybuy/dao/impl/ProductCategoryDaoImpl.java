package com.easybuy.dao.impl;

import com.easybuy.dao.ProductCategoryDao;
import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;
import com.easybuy.util.DataSourceUtil;
import com.easybuy.util.EmptyUtils;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class ProductCategoryDaoImpl extends BaseDaoImpl implements ProductCategoryDao {
    public ProductCategoryDaoImpl(Connection connection) {
        super(connection);
    }

    public static void main(String[] args) {
        ProductCategoryDaoImpl jibai = new ProductCategoryDaoImpl(DataSourceUtil.openConnection());

        ProductCategory ppip = new ProductCategory();

        ppip.setName("JAVData");
        ppip.setParentId(1);
        ppip.setParentName("HD_Video");
        ppip.setType(1);
        ppip.setIconClass("Class");

        //jibai.add(ppip);

        //jibai.deleteById(2);

        ProductCategoryParam gu = new ProductCategoryParam();


        List<ProductCategory> productCategoryList = jibai.ProductCategoryList(gu);

        for (ProductCategory gugugu: productCategoryList) {
            System.out.println(gugugu.getName()+"  "+gugugu.getParentName());
        }
    }

    @Override
    public Integer add(ProductCategory productCategory) {
        Integer cc = 0;

        String sql = " insert into easybuy_product_category " +
                " (name, parentId, type, iconClass) values(?,?,?,?) ";

        Object[] params = { productCategory.getName(), productCategory.getParentId(),
                 productCategory.getType(),productCategory.getIconClass() };

        cc = this.executeInsert(sql, params);

        return cc;
    }

    @Override
    public Integer update(ProductCategory productCategory) {

        String sql = " update easybuy_product_category set name = ?, " +
                " parentId = ?, type = ?, iconClass = ? where id = ?  ";

        Object[] params = { productCategory.getName(), productCategory.getParentId(),
                productCategory.getType(),productCategory.getId() };

        this.executeInsert(sql, params);

        return null;
    }

    @Override
    public void deleteById(Integer id) {
        String sql = " delete from easybuy_product_category where id = ? ";

        Object[] params = { id };

        this.executeUpdate(sql,params);
    }

    @Override
    public Integer count(ProductCategoryParam param) {
        Integer cc = 0;

        StringBuffer sql = new StringBuffer(" select * from easybuy_product_category where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(param.getName())) {
            sql.append(" and name like ? ");
            paramList.add("%"+param.getName()+"%");
        }

        if (EmptyUtils.isNotEmpty(param.getParentId())) {
            sql.append(" and parentId = ? ");

            paramList.add(param.getParentId());
        }

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql.toString(),paramList.toArray());

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
    public ProductCategory ProductCategoryById(Integer id) {

        ProductCategory category = new ProductCategory();

        String sql = " select * from easybuy_product_category where id = ? ";

        Object[] params = {id};

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql,params);

            while (resultSet.next()) {
                category = table2Class(resultSet);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return category;
    }

    @Override
    public List<ProductCategory> ProductCategoryList(ProductCategoryParam param) {

        List<ProductCategory> productCategoryList = new ArrayList<ProductCategory>();

        StringBuffer sql = new StringBuffer(" select epc1.*, epc2.name as parentName " +
                " from easybuy_product_category epc1 " +
                "  left join easybuy_product_category epc2 on epc1.parentId = epc2.id where 1=1 ");

        List<Object> paramList = new ArrayList<Object>();

        if (EmptyUtils.isNotEmpty(param.getName())) {
            sql.append(" and epc1.name like ? ");
            paramList.add("%"+param.getName()+"%");
        }

        if (EmptyUtils.isNotEmpty(param.getParentId())) {
            sql.append(" and epc1.parentId like ? ");
            paramList.add("%"+param.getParentId()+"%");
        }

        if (EmptyUtils.isNotEmpty(param.getType())) {
            sql.append(" and epc1.type = ? ");
            paramList.add("%"+param.getType()+"%");
        }

        if (param.isPage()) {
            sql.append(" limit  " + param.getStartIndex() + "," + param.getPageSize());
        }

        ResultSet resultSet = null;

        try {
            resultSet = this.executeQuery(sql.toString(),paramList.toArray());

            while (resultSet.next()) {
                ProductCategory pl = this.table2Class(resultSet);
                pl.setParentName(resultSet.getString("parentName"));
                productCategoryList.add(pl);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            this.closeResource();
            this.closeResource(resultSet);
        }

        return productCategoryList;
    }

    @Override
    public ProductCategory table2Class(ResultSet rs) throws Exception {

        ProductCategory nigga = new ProductCategory();

        nigga.setId(rs.getInt("id"));
        nigga.setName(rs.getString("name"));
        nigga.setParentId(rs.getInt("parentId"));
        nigga.setType(rs.getInt("type"));
        nigga.setIconClass(rs.getString("iconClass"));

        return nigga;
    }
}
