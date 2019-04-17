package com.easybuy.util;

import java.io.Serializable;

public class Pager implements Serializable {
    private int rowCount;
    private int rowPerpage;
    private int pageCount;
    private int currentPage;

    private String url;

    public int getRowCount() {
        return rowCount;
    }

    public void setRowCount(int rowCount) {
        this.rowCount = rowCount;
    }

    public int getRowPerpage() {
        return rowPerpage;
    }

    public void setRowPerpage(int rowPerpage) {
        this.rowPerpage = rowPerpage;
    }

    public int getPageCount() {
        return pageCount;
    }

    public void setPageCount(int pageCount) {
        this.pageCount = pageCount;
    }

    public int getCurrentPage() {
        return currentPage;
    }

    public void setCurrentPage(int currentPage) {
        this.currentPage = currentPage;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public Pager(int rowCount, int rowPerpage, int currentPage) {
        this.rowCount = rowCount;
        this.rowPerpage = rowPerpage;
        this.currentPage = currentPage;

        if (this.rowCount % this.rowPerpage == 0) {
            this.pageCount = this.rowCount / this.rowPerpage;
        }
        else if (this.rowCount % this.rowPerpage > 0) {
            this.pageCount = this.rowCount / this.rowPerpage +1;
        }
        else {
            this.pageCount = 0;
        }
    }
}
