package com.easybuy.web.backend;


import java.io.File;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;

import com.easybuy.biz.ProductBiz;
import com.easybuy.biz.ProductCategoryBiz;
import com.easybuy.biz.impl.ProductBizImpl;
import com.easybuy.biz.impl.ProductCategoryBizImpl;
import com.easybuy.entity.Product;
import com.easybuy.entity.ProductCategory;
import com.easybuy.param.ProductCategoryParam;
import com.easybuy.util.EmptyUtils;
import com.easybuy.util.Pager;
import com.easybuy.util.ReturnResult;
import com.easybuy.util.StringUtils;
import com.easybuy.web.AbstractServlet;

/**
 * @author MrWang
 */
@WebServlet(urlPatterns = {"/admin/product"}, name = "adminProduct")
public class AdminProductServlet extends AbstractServlet {

    private ProductCategoryBiz productCategoryBiz;
    private static final String TMP_DIR_PATH = "c:\\tmp";
    private File tmpDir;
    private static final String DESTINATION_DIR_PATH = "/files";
    private File destinationDir;
    private ProductBiz productBiz;

    public void init(ServletConfig config) throws ServletException {
        super.init(config);
        tmpDir = new File(TMP_DIR_PATH);
        if (!tmpDir.exists()) {
            tmpDir.mkdirs();
        }
        String realPath = getServletContext().getRealPath(DESTINATION_DIR_PATH);
        destinationDir = new File(realPath);
        destinationDir.mkdirs();
        if (!destinationDir.isDirectory()) {
            throw new ServletException(DESTINATION_DIR_PATH
                    + " is not a directory");
        }
        productBiz = new ProductBizImpl();
        productCategoryBiz = new ProductCategoryBizImpl();
    }

    /**
     * @param request
     * @param response
     * @return
     */
    public String index(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String currentPageStr = request.getParameter("currentPage");
        String pageSize = request.getParameter("pageSize");
        int rowPerPage = EmptyUtils.isEmpty(pageSize) ? 5 : Integer.parseInt(pageSize);
        int currentPage = EmptyUtils.isEmpty(currentPageStr) ? 1 : Integer.parseInt(currentPageStr);
        int total = productBiz.queryProductCount(null, null, null);
        Pager pager = new Pager(total, rowPerPage, currentPage);
        pager.setUrl("/admin/product?action=index");
        List<Product> productList = productBiz.getProductList(currentPage, rowPerPage, null, null, null);
        request.setAttribute("productList", productList);
        request.setAttribute("pager", pager);
        request.setAttribute("menu", 5);
        return "/backend/product/productList";
    }

    /**
     * @return
     */
    public String toAddProduct(HttpServletRequest request, HttpServletResponse response) throws Exception {
        request.setAttribute("menu", 6);
        request.setAttribute("product", new Product());
        ProductCategoryParam params = new ProductCategoryParam();
        params.setType(1);
        List<ProductCategory> productCategoryList = productCategoryBiz.ProductCategoryList(params);
        request.setAttribute("productCategoryList1", productCategoryList);
        return "/backend/product/toAddProduct";
    }

    /**
     * @param request
     * @param response
     * @throws Exception
     */
    public void addProduct(HttpServletRequest request, HttpServletResponse response) throws Exception {
        Map<String, String> params = new HashMap<String, String>();
        Product product = null;
        DiskFileItemFactory fileItemFactory = new DiskFileItemFactory();
        fileItemFactory.setSizeThreshold(1 * 1024 * 1024); // 1 MB
        fileItemFactory.setRepository(tmpDir);
        String fileName = null;
        ServletFileUpload uploadHandler = new ServletFileUpload(fileItemFactory);
        uploadHandler.setHeaderEncoding("utf-8");
        try {
            List items = uploadHandler.parseRequest(request);
            Iterator itr = items.iterator();
            while (itr.hasNext()) {
                FileItem item = (FileItem) itr.next();
                if (item.isFormField()) {
                    params.put(item.getFieldName(), item.getString("utf-8"));
                } else {
                    if (item.getSize() > 0) {
                        fileName = item.getName().substring(
                                item.getName().lastIndexOf("."));
                        File file = new File(destinationDir, fileName);
                        fileName = StringUtils.randomUUID()
                                + item.getName().substring(
                                item.getName().lastIndexOf("."));
                        file = new File(destinationDir, fileName);
                        item.write(file);
                    }
                }
            }

            product = copyToProduct(params);
            product.setFileName(fileName);
            Integer id = product.getId();
            if (EmptyUtils.isEmpty(id) || id.equals("0")) {
                productBiz.add(product);
            } else {
                if (EmptyUtils.isEmpty(product.getFileName()) || product.getFileName().length() < 5) {
                    Product productDemo = productBiz.getProductById(id);
                    product.setFileName(productDemo.getFileName());
                }
                productBiz.update(product);
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
        response.sendRedirect(request.getContextPath() + "/admin/product?action=index");
    }

    /**
     * @return
     */
    public String toUpdateProduct(HttpServletRequest request, HttpServletResponse response) throws Exception {
        String id = request.getParameter("id");
        Product product = productBiz.getProductById(Integer.valueOf(id));
        request.setAttribute("menu", 6);

        ProductCategoryParam params = new ProductCategoryParam();
        params.setType(1);
        List<ProductCategory> productCategoryList1 = productCategoryBiz.ProductCategoryList(params);
        params.setType(2);
        List<ProductCategory> productCategoryList2 = productCategoryBiz.ProductCategoryList(params);
        params.setType(3);
        List<ProductCategory> productCategoryList3 = productCategoryBiz.ProductCategoryList(params);

        request.setAttribute("productCategoryList1", productCategoryList1);
        request.setAttribute("productCategoryList2", productCategoryList2);
        request.setAttribute("productCategoryList3", productCategoryList3);
        request.setAttribute("product", product);
        return "/backend/product/toAddProduct";
    }

    /**
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ReturnResult deleteById(HttpServletRequest request, HttpServletResponse response) throws Exception {
        ReturnResult result = new ReturnResult();
        String id = request.getParameter("id");
        productBiz.deleteProductById(Integer.parseInt(id));
        result.returnSuccess();
        return result;
    }

    private Product copyToProduct(Map<String, String> params) throws Exception {
        Product product = new Product();
        String id = params.get("id");
        String name = params.get("name");
        String description = params.get("description");
        String price = params.get("price");
        String stock = params.get("stock");
        String categoryLevel1Id = params.get("categoryLevel1Id");
        String categoryLevel2Id = params.get("categoryLevel2Id");
        String categoryLevel3Id = params.get("categoryLevel3Id");
        product.setName(name);
        product.setDescription(description);
        product.setPrice(Float.valueOf(price));
        product.setStock(Integer.parseInt(stock));
        product.setCategoryLevel1(EmptyUtils.isNotEmpty(categoryLevel1Id) ? Integer.parseInt(categoryLevel1Id) : 0);
        product.setCategoryLevel2(EmptyUtils.isNotEmpty(categoryLevel2Id) ? Integer.parseInt(categoryLevel2Id) : 0);
        product.setCategoryLevel3(EmptyUtils.isNotEmpty(categoryLevel3Id) ? Integer.parseInt(categoryLevel3Id) : 0);
        product.setId(EmptyUtils.isNotEmpty(id) ? Integer.parseInt(id) : null);
        return product;
    }

    @Override
    public Class getServletClass() {
        return AdminProductServlet.class;
    }
}
