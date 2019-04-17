package com.easybuy.biz;

import com.easybuy.entity.UserAddress;

import java.util.List;

public interface UserAddressBiz {
    List<UserAddress> queryUserAddressList(Integer id);

    Integer addUserAddress(Integer id, String address, String remark);

    UserAddress getUserAddressById(Integer addressId);
}
