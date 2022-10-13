/*
    rgb2yuv - Code covered by the MIT License
    Author: mutouyun (http://orzz.org)
*/

////////////////////////////////////////////////////////////////
/// It's a pixel walker to walk each pixel and execute a closure with it.
////////////////////////////////////////////////////////////////

/* 888 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_888 && F::iterator_size == 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size % sizeof(R2Y_ rgb_t)) == 0); // 3 input bytes convert to 1 pixel
    R2Y_ rgb_t * cur_pixel = reinterpret_cast<R2Y_ rgb_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += 3, ++cur_pixel)
    {
        STD_ forward<T>(do_sth)(*cur_pixel);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_888 && F::iterator_size > 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size % sizeof(R2Y_ rgb_t)) == 0); // 3 input bytes convert to 1 pixel
    R2Y_ rgb_t * cur_pixel = reinterpret_cast<R2Y_ rgb_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += (3 * F::iterator_size), cur_pixel += F::iterator_size)
    {
        STD_ forward<T>(do_sth)(*reinterpret_cast<R2Y_ rgb_t (*)[F::iterator_size]>(& cur_pixel));
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_888 && F::iterator_size > 1 && F::is_block == 1)>
{
    assert((in_w % F::iterator_size) == 0);
    assert((in_h % F::iterator_size) == 0);
    R2Y_ rgb_t tmp[F::iterator_size * F::iterator_size];
    GLB_ size_t row_offset = in_w - F::iterator_size;
    R2Y_ rgb_t * cur_pixel = reinterpret_cast<R2Y_ rgb_t *>(in_data);
    for (GLB_ size_t i = 0; i < in_h; i += F::iterator_size, cur_pixel += (in_w * (F::iterator_size - 1)))
    {
        for (GLB_ size_t j = 0; j < in_w; j += F::iterator_size, cur_pixel += F::iterator_size)
        {
            R2Y_ rgb_t * block_iter = cur_pixel;
            for (int n = 0, index = 0; n < F::iterator_size; ++n, block_iter += row_offset)
            {
                for (int m = 0; m < F::iterator_size; ++m, ++index, ++block_iter)
                {
                    tmp[index] = *block_iter;
                }
            }
            STD_ forward<T>(do_sth)(tmp);
        }
    }
}

/* 565 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_565 && F::iterator_size == 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size & 1) == 0); // in_size must be an even number
    R2Y_ rgb_t tmp;
    GLB_ uint16_t * cur_pixel = reinterpret_cast<GLB_ uint16_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += 2, ++cur_pixel)
    {
        tmp.r_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0xF800) >> 8 );
        tmp.g_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x07E0) >> 3 );
        tmp.b_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x001F) << 3 );
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_565 && F::iterator_size > 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size & 1) == 0); // in_size must be an even number
    R2Y_ rgb_t tmp[F::iterator_size];
    GLB_ uint16_t * cur_pixel = reinterpret_cast<GLB_ uint16_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += (2 * F::iterator_size))
    {
        for (int n = 0; n < F::iterator_size; ++n, ++cur_pixel)
        {
            R2Y_ rgb_t & ref = tmp[n];
            ref.r_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0xF800) >> 8 );
            ref.g_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x07E0) >> 3 );
            ref.b_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x001F) << 3 );
        }
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_565 && F::iterator_size > 1 && F::is_block == 1)>
{
    assert((in_w % F::iterator_size) == 0);
    assert((in_h % F::iterator_size) == 0);
    R2Y_ rgb_t tmp[F::iterator_size * F::iterator_size];
    GLB_ size_t row_offset = in_w - F::iterator_size;
    GLB_ uint16_t * cur_pixel = reinterpret_cast<GLB_ uint16_t *>(in_data);
    for (GLB_ size_t i = 0; i < in_h; i += F::iterator_size, cur_pixel += (in_w * (F::iterator_size - 1)))
    {
        for (GLB_ size_t j = 0; j < in_w; j += F::iterator_size, cur_pixel += F::iterator_size)
        {
            GLB_ uint16_t * block_iter = cur_pixel;
            for (int n = 0, index = 0; n < F::iterator_size; ++n, block_iter += row_offset)
            {
                for (int m = 0; m < F::iterator_size; ++m, ++index, ++block_iter)
                {
                    R2Y_ rgb_t & ref = tmp[index];
                    ref.r_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0xF800) >> 8 );
                    ref.g_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x07E0) >> 3 );
                    ref.b_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x001F) << 3 );
                }
            }
            STD_ forward<T>(do_sth)(tmp);
        }
    }
}

/* 555 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_555 && F::iterator_size == 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size & 1) == 0); // in_size must be an even number
    R2Y_ rgb_t tmp;
    GLB_ uint16_t * cur_pixel = reinterpret_cast<GLB_ uint16_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += 2, ++cur_pixel)
    {
        tmp.r_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x7C00) >> 7 );
        tmp.g_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x03E0) >> 2 );
        tmp.b_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x001F) << 3 );
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_555 && F::iterator_size > 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size & 1) == 0); // in_size must be an even number
    R2Y_ rgb_t tmp[F::iterator_size];
    GLB_ uint16_t * cur_pixel = reinterpret_cast<GLB_ uint16_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += (2 * F::iterator_size))
    {
        for (int n = 0; n < F::iterator_size; ++n, ++cur_pixel)
        {
            R2Y_ rgb_t & ref = tmp[n];
            ref.r_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x7C00) >> 7 );
            ref.g_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x03E0) >> 2 );
            ref.b_ = static_cast<GLB_ uint8_t>( ((*cur_pixel) & 0x001F) << 3 );
        }
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_555 && F::iterator_size > 1 && F::is_block == 1)>
{
    assert((in_w % F::iterator_size) == 0);
    assert((in_h % F::iterator_size) == 0);
    R2Y_ rgb_t tmp[F::iterator_size * F::iterator_size];
    GLB_ size_t row_offset = in_w - F::iterator_size;
    GLB_ uint16_t * cur_pixel = reinterpret_cast<GLB_ uint16_t *>(in_data);
    for (GLB_ size_t i = 0; i < in_h; i += F::iterator_size, cur_pixel += (in_w * (F::iterator_size - 1)))
    {
        for (GLB_ size_t j = 0; j < in_w; j += F::iterator_size, cur_pixel += F::iterator_size)
        {
            GLB_ uint16_t * block_iter = cur_pixel;
            for (int n = 0, index = 0; n < F::iterator_size; ++n, block_iter += row_offset)
            {
                for (int m = 0; m < F::iterator_size; ++m, ++index, ++block_iter)
                {
                    R2Y_ rgb_t & ref = tmp[index];
                    ref.r_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x7C00) >> 7 );
                    ref.g_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x03E0) >> 2 );
                    ref.b_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x001F) << 3 );
                }
            }
            STD_ forward<T>(do_sth)(tmp);
        }
    }
}

/* 444 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_444 && F::iterator_size == 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size % 3) == 0); // 3 input bytes convert to 2 pixels (6 bytes)
    R2Y_ rgb_t tmp;
    for (GLB_ size_t i = 0; i < size; i += 3)
    {
        tmp.b_ = static_cast<GLB_ uint8_t>( ((*in_data) & 0x0F) << 4 );
        tmp.g_ = static_cast<GLB_ uint8_t>  ((*in_data) & 0xF0);        ++in_data;
        tmp.r_ = static_cast<GLB_ uint8_t>( ((*in_data) & 0x0F) << 4 );
        STD_ forward<T>(do_sth)(tmp);
        tmp.b_ = static_cast<GLB_ uint8_t>  ((*in_data) & 0xF0);        ++in_data;
        tmp.g_ = static_cast<GLB_ uint8_t>( ((*in_data) & 0x0F) << 4 );
        tmp.r_ = static_cast<GLB_ uint8_t>  ((*in_data) & 0xF0);        ++in_data;
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_444 && F::iterator_size > 1 && (F::iterator_size & 1) == 0 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size % 3) == 0); // 3 input bytes convert to 2 pixels (6 bytes)
    R2Y_ rgb_t tmp[F::iterator_size];
    for (GLB_ size_t i = 0; i < size; i += (3 * (F::iterator_size >> 1)))
    {
        for (int n = 0; n < F::iterator_size;)
        {
            {
                R2Y_ rgb_t & ref = tmp[n]; ++n;
                ref.b_ = static_cast<GLB_ uint8_t>( ((*in_data) & 0x0F) << 4 );
                ref.g_ = static_cast<GLB_ uint8_t>  ((*in_data) & 0xF0); ++in_data;
                ref.r_ = static_cast<GLB_ uint8_t>( ((*in_data) & 0x0F) << 4 );
            }
            {
                R2Y_ rgb_t & ref = tmp[n]; ++n;
                ref.b_ = static_cast<GLB_ uint8_t>  ((*in_data) & 0xF0); ++in_data;
                ref.g_ = static_cast<GLB_ uint8_t>( ((*in_data) & 0x0F) << 4 );
                ref.r_ = static_cast<GLB_ uint8_t>  ((*in_data) & 0xF0); ++in_data;
            }
        }
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_444 && F::iterator_size > 1 && (F::iterator_size & 1) == 0 && F::is_block == 1)>
{
    assert((in_w % F::iterator_size) == 0);
    assert((in_h % F::iterator_size) == 0);
    R2Y_ rgb_t tmp[F::iterator_size * F::iterator_size];
    GLB_ size_t row_offset = ((in_w - F::iterator_size) >> 1) * 3;
    for (GLB_ size_t i = 0; i < in_h; i += F::iterator_size, in_data += (in_w * (((F::iterator_size - 1) * 3) >> 1)))
    {
        for (GLB_ size_t j = 0; j < in_w; j += F::iterator_size, in_data += (3 * (F::iterator_size >> 1)))
        {
            R2Y_ byte_t * block_iter = in_data;
            for (int n = 0, index = 0; n < F::iterator_size; ++n, block_iter += row_offset)
            {
                for (int m = 0; m < F::iterator_size; m += 2)
                {
                    {
                        R2Y_ rgb_t & ref = tmp[index]; ++index;
                        ref.b_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x0F) << 4 );
                        ref.g_ = static_cast<GLB_ uint8_t>  ((*block_iter) & 0xF0); ++block_iter;
                        ref.r_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x0F) << 4 );
                    }
                    {
                        R2Y_ rgb_t & ref = tmp[index]; ++index;
                        ref.b_ = static_cast<GLB_ uint8_t>  ((*block_iter) & 0xF0); ++block_iter;
                        ref.g_ = static_cast<GLB_ uint8_t>( ((*block_iter) & 0x0F) << 4 );
                        ref.r_ = static_cast<GLB_ uint8_t>  ((*block_iter) & 0xF0); ++block_iter;
                    }
                }
            }
            STD_ forward<T>(do_sth)(tmp);
        }
    }
}

/* 888X */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_888X && F::iterator_size == 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size % 4) == 0); // 4 input bytes convert to 1 pixel (3 bytes)
    GLB_ uint32_t * cur_pixel = reinterpret_cast<GLB_ uint32_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += 4, ++cur_pixel)
    {
        STD_ forward<T>(do_sth)(*reinterpret_cast<R2Y_ rgb_t *>(cur_pixel));
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_888X && F::iterator_size > 1 && F::is_block == 0)>
{
    GLB_ size_t size = calculate_size<S>(in_w, in_h);
    assert((size % 4) == 0); // 4 input bytes convert to 1 pixel (3 bytes)
    R2Y_ rgb_t tmp[F::iterator_size];
    GLB_ uint32_t * cur_pixel = reinterpret_cast<GLB_ uint32_t *>(in_data);
    for (GLB_ size_t i = 0; i < size; i += (4 * F::iterator_size))
    {
        for (int n = 0; n < F::iterator_size; ++n, ++cur_pixel)
        {
            tmp[n] = *reinterpret_cast<R2Y_ rgb_t *>(cur_pixel);
        }
        STD_ forward<T>(do_sth)(tmp);
    }
}

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ rgb_888X && F::iterator_size > 1 && F::is_block == 1)>
{
    assert((in_w % F::iterator_size) == 0);
    assert((in_h % F::iterator_size) == 0);
    R2Y_ rgb_t tmp[F::iterator_size * F::iterator_size];
    GLB_ size_t row_offset = in_w - F::iterator_size;
    GLB_ uint32_t * cur_pixel = reinterpret_cast<GLB_ uint32_t *>(in_data);
    for (GLB_ size_t i = 0; i < in_h; i += F::iterator_size, cur_pixel += (in_w * (F::iterator_size - 1)))
    {
        for (GLB_ size_t j = 0; j < in_w; j += F::iterator_size, cur_pixel += F::iterator_size)
        {
            GLB_ uint32_t * block_iter = cur_pixel;
            for (int n = 0, index = 0; n < F::iterator_size; ++n, block_iter += row_offset)
            {
                for (int m = 0; m < F::iterator_size; ++m, ++index, ++block_iter)
                {
                    tmp[index] = *reinterpret_cast<R2Y_ rgb_t *>(block_iter);
                }
            }
            STD_ forward<T>(do_sth)(tmp);
        }
    }
}

#pragma push_macro("R2Y_HELPER_")
#undef  R2Y_HELPER_
#define R2Y_HELPER_ R2Y_ detail_helper_::

/* YUYV/YVYU/UYVY/VYUY */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<((S == R2Y_ yuv_YUYV || S == R2Y_ yuv_YVYU ||
                          S == R2Y_ yuv_UYVY || S == R2Y_ yuv_VYUY) && F::iterator_size == 1 && F::is_block == 0)>
{
    auto yuv = reinterpret_cast<R2Y_HELPER_ packed_yuv_t<S>*>(in_data);
    for (GLB_ size_t i = 0; i < (in_w * in_h); i += R2Y_ iterator<S>::iterator_size, ++yuv)
    {
        R2Y_ yuv_t tmp[R2Y_ iterator<S>::iterator_size] =
        {
            { yuv->cr_, yuv->cb_, yuv->y0_ },
            { yuv->cr_, yuv->cb_, yuv->y1_ }
        };
        STD_ forward<T>(do_sth)(tmp);
    }
}

/* Y41P */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ yuv_Y41P && F::iterator_size == 1 && F::is_block == 0)>
{
    auto yuv = reinterpret_cast<R2Y_HELPER_ packed_yuv_t<S>*>(in_data);
    for (GLB_ size_t i = 0; i < (in_w * in_h); i += R2Y_ iterator<S>::iterator_size, ++yuv)
    {
        R2Y_ yuv_t tmp[R2Y_ iterator<S>::iterator_size] =
        {
            { yuv->v0_, yuv->u0_, yuv->y0_ },
            { yuv->v0_, yuv->u0_, yuv->y1_ },
            { yuv->v0_, yuv->u0_, yuv->y2_ },
            { yuv->v0_, yuv->u0_, yuv->y3_ },
            { yuv->v1_, yuv->u1_, yuv->y4_ },
            { yuv->v1_, yuv->u1_, yuv->y5_ },
            { yuv->v1_, yuv->u1_, yuv->y6_ },
            { yuv->v1_, yuv->u1_, yuv->y7_ }
        };
        STD_ forward<T>(do_sth)(tmp);
    }
}

/* Y411 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<(S == R2Y_ yuv_Y411 && F::iterator_size == 1 && F::is_block == 0)>
{
    auto yuv = reinterpret_cast<R2Y_HELPER_ packed_yuv_t<S>*>(in_data);
    for (GLB_ size_t i = 0; i < (in_w * in_h); i += R2Y_ iterator<S>::iterator_size, ++yuv)
    {
        R2Y_ yuv_t tmp[R2Y_ iterator<S>::iterator_size] =
        {
            { yuv->cr_, yuv->cb_, yuv->y0_ },
            { yuv->cr_, yuv->cb_, yuv->y1_ },
            { yuv->cr_, yuv->cb_, yuv->y2_ },
            { yuv->cr_, yuv->cb_, yuv->y3_ }
        };
        STD_ forward<T>(do_sth)(tmp);
    }
}

/* NV24/NV42 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<((S == R2Y_ yuv_NV24 || S == R2Y_ yuv_NV42) && F::iterator_size == 1 && F::is_block == 0)>
{
    R2Y_ byte_t * y = nullptr;
    R2Y_HELPER_ planar_uv_t<S> uv;
    R2Y_HELPER_ yuv_planar <S>(y, uv, in_data, in_w, in_h);
    for (GLB_ size_t i = 0; i < (in_w * in_h); ++i, ++y, ++(uv.uv_))
    {
        STD_ forward<T>(do_sth)(R2Y_ yuv_t { uv.uv_->cr_, uv.uv_->cb_, *y });
    }
}

/* YV12/YU12/NV12/NV21 */

template <R2Y_ supported S, typename T, typename F = STD_ remove_reference_t<T>>
auto pixel_foreach(R2Y_ byte_t * in_data, GLB_ size_t in_w, GLB_ size_t in_h, T && do_sth)
    -> STD_ enable_if_t<((S == R2Y_ yuv_YV12 || S == R2Y_ yuv_YU12 ||
                          S == R2Y_ yuv_NV12 || S == R2Y_ yuv_NV21) && F::iterator_size == 1 && F::is_block == 0)>
{
    R2Y_ byte_t * y = nullptr;
    R2Y_HELPER_ planar_uv_t<S> uv;
    R2Y_HELPER_ yuv_planar <S>(y, uv, in_data, in_w, in_h);
    R2Y_HELPER_ planar_uv_t<S> uv1 = uv;
    for (GLB_ size_t i = 0; i < in_h; i += 2)
    {
        for (GLB_ size_t j = 0; j < in_w; j += 2)
        {
            R2Y_ yuv_t tmp[2];
            tmp[0].y_ = *y; ++y;
            tmp[1].y_ = *y; ++y;
            R2Y_HELPER_  get_planar_uv(tmp[0].u_, tmp[0].v_, uv);
            R2Y_HELPER_  get_planar_uv(tmp[1].u_, tmp[1].v_, uv);
            R2Y_HELPER_ next_planar_uv(uv);
            STD_ forward<T>(do_sth)(tmp);
        }
        for (GLB_ size_t j = 0; j < in_w; j += 2)
        {
            R2Y_ yuv_t tmp[2];
            tmp[0].y_ = *y; ++y;
            tmp[1].y_ = *y; ++y;
            R2Y_HELPER_  get_planar_uv(tmp[0].u_, tmp[0].v_, uv1);
            R2Y_HELPER_  get_planar_uv(tmp[1].u_, tmp[1].v_, uv1);
            R2Y_HELPER_ next_planar_uv(uv1);
            STD_ forward<T>(do_sth)(tmp);
        }
    }
}

#pragma pop_macro("R2Y_HELPER_")
