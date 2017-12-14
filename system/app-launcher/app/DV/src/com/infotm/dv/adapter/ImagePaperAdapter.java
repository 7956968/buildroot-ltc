package com.infotm.dv.adapter;

import java.util.ArrayList;

import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;
import android.widget.ImageView;

public class ImagePaperAdapter extends PagerAdapter {

	private ArrayList<ImageView>list;
	public ImagePaperAdapter(ArrayList<ImageView> list) {
		this.list = list;
	}

	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return list.size();
	}

	@Override
	public boolean isViewFromObject(View arg0, Object arg1) {
		// TODO Auto-generated method stub
		return arg0 == arg1;
	}
	
    @Override    
    public void destroyItem(ViewGroup container, int position,    
            Object object) {    
        //Warning����Ҫ���������removeView  
    }
	
	@Override
	public Object instantiateItem(ViewGroup container, int position) {
		// TODO Auto-generated method stub

		
		ImageView view = list.get(position) ;
		ViewParent vp =  view.getParent();
		if(vp != null){
			ViewGroup parent = (ViewGroup)vp;
			parent.removeView(view);
		}
		//������Щ��������ϣ�������ӵĻ����ͻ�������û��������ĸ���ʱ��ͻᴥ������쳣
		//ԭ����������ͼ��һ���и������View��ӵ���һ�������
		((ViewPager)container).addView(list.get(position));
		
		System.out.println("------------");
		return list.get(position);
	}

}
