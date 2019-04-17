package com.easybuy.param;

import com.easybuy.entity.ProductCategory;

public class ProductCategoryParam extends ProductCategory {
    private Integer startIndex;
    private Integer pageSize;
    private String sort;
    private boolean isPage = false;


    /**
     * to provide split info
     *
     */
    public void openPage (Integer startIndex, Integer pageSize) {
        this.isPage = true;
        this.startIndex = startIndex;
        this.pageSize = pageSize;
    }

    public Integer getStartIndex() {
        return startIndex;
    }

    public void setStartIndex(Integer startIndex) {
        this.startIndex = startIndex;
    }

    public Integer getPageSize() {
        return pageSize;
    }

    public void setPageSize(Integer pageSize) {
        this.pageSize = pageSize;
    }

    public String getSort() {
        return sort;
    }

    public void setSort(String sort) {
        this.sort = sort;
    }

    public boolean isPage() {
        return isPage;
    }

    public void setPage(boolean page) {
        isPage = page;
    }
}
