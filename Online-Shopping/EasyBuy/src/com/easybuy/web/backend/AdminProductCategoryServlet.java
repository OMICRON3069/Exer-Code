package com.easybuy.web.backend;


import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.biz.impl.ProductCategoryBizImpl;
import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;
import com.easybuy.util.Constants;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;
import com.easybuy.util.ReturnResult;
import com.easybuy.web.AbstractServlet;

@WebServlet(urlPatterns = {"/admin/productCategory"}, name = "adminProductCategory")
public class AdminProductCategoryServlet extends AbstractServlet {

    private ProductCategoryBiz productCategoryBiz;

    private ProductBiz productBiz;

    public void init() throws ServletException {
        this.productCategoryBiz = new ProductCategoryBizImpl();
        this.productBiz = new ProductBizImpl();
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String index(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String currentPageStr = request.getParameter("currentPage");
        String pageSize = request.getParameter("pageSize");
        int rowPerPage = EmptyUtils.isEmpty(pageSize) ? 8 : Integer.parseInt(pageSize);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        ProductCategoryParam params = new ProductCategoryParam();
        int total = productCategoryBiz.Count(params);
        Pager pager = new Pager(total, rowPerPage, currentPage);
        params.openPage((pager.getCurrentPage() - 1) * pager.getRowPerpage(), pager.getRowPerpage());
        pager.setUrl("/admin/productCategory?action=index");
        List<ProductCategory> productCategoryList = productCategoryBiz.ProductCategoryList(params);
        request.setAttribute("productCategoryList", productCategoryList);
        request.setAttribute("pager", pager);
        request.setAttribute("menu", 4);
        return "/backend/productCategory/productCategoryList";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String toAddProductCategory(HttpServletRequest request, HttpServletResponse response) throws Exception {
        List<ProductCategory> productCategoryList = null;
        ProductCategoryParam params = new ProductCategoryParam();
        params.setType(1);
        productCategoryList = productCategoryBiz.ProductCategoryList(params);
        request.setAttribute("productCategoryList1", productCategoryList);
        request.setAttribute("productCategory", new ProductCategory());
        return "/backend/productCategory/toAddProductCategory";
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String toUpdateProductCategory(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        ProductCategory productCategory = productCategoryBiz.ProductCategoryById(Integer.valueOf(id));
        List<ProductCategory> productCategoryList1 = null;
        List<ProductCategory> productCategoryList2 = null;
        List<ProductCategory> productCategoryList3 = null;
        request.setAttribute("productCategory", productCategory);
        if (productCategory.getType() >= 1) {
            ProductCategoryParam params = new ProductCategoryParam();
            params.setType(1);
            productCategoryList1 = productCategoryBiz.ProductCategoryList(params);
        }
        if (productCategory.getType() >= 2) {
            ProductCategoryParam params = new ProductCategoryParam();
            params.setType(2);
            productCategoryList2 = productCategoryBiz.ProductCategoryList(params);
            request.setAttribute("parentProductCategory", productCategoryBiz.ProductCategoryById(productCategory.getParentId()));
        }
        if (productCategory.getType() >= 3) {
            List<ProductCategory> productCategoryList = null;
            ProductCategoryParam params = new ProductCategoryParam();
            params.setType(3);
            productCategoryList3 = productCategoryBiz.ProductCategoryList(params);
        }
        request.setAttribute("productCategoryList1", productCategoryList1);
        request.setAttribute("productCategoryList2", productCategoryList2);
        request.setAttribute("productCategoryList3", productCategoryList3);
        return "/backend/productCategory/toAddProductCategory";
    }

    /**
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ReturnResult queryProductCategoryList(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        String parentId = request.getParameter("parentId");
        List<ProductCategory> productCategoryList = null;
        ProductCategoryParam params = new ProductCategoryParam();
        params.setParentId(EmptyUtils.isEmpty(parentId) ? 0 : Integer.parseInt(parentId));
        productCategoryList = productCategoryBiz.ProductCategoryList(params);
        result.setStatus(Constants.ReturnResult.SUCCESS);
        result.setData(productCategoryList);
        return result;
    }

    /**
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ReturnResult modifyProductCategory(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        Integer parentId = 0;
        String id = request.getParameter("id");
        String productCategoryLevel1 = request.getParameter("productCategoryLevel1");
        String productCategoryLevel2 = request.getParameter("productCategoryLevel2");
        String name = request.getParameter("name");
        String type = request.getParameter("type");
        if (type.equals("1")) {
            parentId = 0;
        } else if (type.equals("2")) {
            parentId = Integer.parseInt(productCategoryLevel1);
        } else {
            parentId = Integer.parseInt(productCategoryLevel2);
        }
        ProductCategory productCategory = new ProductCategory();
        productCategory.setId(Integer.parseInt(id));
        productCategory.setParentId(parentId);
        productCategory.setName(name);
        productCategory.setType(Integer.parseInt(type));
        productCategoryBiz.updateProductCategory(productCategory);
        result.returnSuccess();
        return result;
    }

    /**
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ReturnResult addProductCategory(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        Integer parentId = 0;
        String type = request.getParameter("type");
        String productCategoryLevel1 = request.getParameter("productCategoryLevel1");
        String productCategoryLevel2 = request.getParameter("productCategoryLevel2");
        String name = request.getParameter("name");
        if (type.equals("1")) {
            parentId = 0;
        } else if (type.equals("2")) {
            parentId = Integer.parseInt(productCategoryLevel1);
        } else {
            parentId = Integer.parseInt(productCategoryLevel2);
        }
        ProductCategory productCategory = new ProductCategory();
        productCategory.setName(name);
        productCategory.setParentId(parentId);
        productCategory.setType(Integer.parseInt(type));
        productCategory.setIconClass("");
        productCategoryBiz.addProductCategory(productCategory);
        result.returnSuccess();
        return result;
    }

    /**
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ReturnResult deleteProductCategory(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        String id = request.getParameter("id");
        String type = request.getParameter("type");
        ProductCategoryParam productCategoryParam = new ProductCategoryParam();
        productCategoryParam.setParentId(Integer.parseInt(id));
        int count = productCategoryBiz.Count(productCategoryParam);
        if (count > 0) {
            return result.returnFail("�Ѵ����ӷ���,����ɾ��");
        }
        count = productBiz.queryProductCount(null, Integer.parseInt(id), Integer.parseInt(type));
        if (count > 0) {
            return result.returnFail("�Ѵ�����Ʒ,����ɾ��");
        }
        productCategoryBiz.deleteById(Integer.parseInt(id));
        result.returnSuccess();
        return result;
    }

    @Override
    public Class getServletClass() {
        return AdminProductCategoryServlet.class;
    }
}
