/*
 * Copyright 2007 Stephane Marchesin
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "drmP.h"
#include "drm.h"
#include "nouveau_drm.h"
#include "nouveau_drv.h"

static uint32_t nv04_graph_ctx_regs [] = {
	NV04_PGRAPH_CTX_SWITCH1,
	NV04_PGRAPH_CTX_SWITCH2,
	NV04_PGRAPH_CTX_SWITCH3,
	NV04_PGRAPH_CTX_SWITCH4,
	NV04_PGRAPH_CTX_CACHE1,
	NV04_PGRAPH_CTX_CACHE2,
	NV04_PGRAPH_CTX_CACHE3,
	NV04_PGRAPH_CTX_CACHE4,
	0x00400184,
	0x004001a4,
	0x004001c4,
	0x004001e4,
	0x00400188,
	0x004001a8,
	0x004001c8,
	0x004001e8,
	0x0040018c,
	0x004001ac,
	0x004001cc,
	0x004001ec,
	0x00400190,
	0x004001b0,
	0x004001d0,
	0x004001f0,
	0x00400194,
	0x004001b4,
	0x004001d4,
	0x004001f4,
	0x00400198,
	0x004001b8,
	0x004001d8,
	0x004001f8,
	0x0040019c,
	0x004001bc,
	0x004001dc,
	0x004001fc,
	0x00400174,
	NV04_PGRAPH_DMA_START_0,
	NV04_PGRAPH_DMA_START_1,
	NV04_PGRAPH_DMA_LENGTH,
	NV04_PGRAPH_DMA_MISC,
	NV04_PGRAPH_DMA_PITCH,
	NV04_PGRAPH_BOFFSET0,
	NV04_PGRAPH_BBASE0,
	NV04_PGRAPH_BLIMIT0,
	NV04_PGRAPH_BOFFSET1,
	NV04_PGRAPH_BBASE1,
	NV04_PGRAPH_BLIMIT1,
	NV04_PGRAPH_BOFFSET2,
	NV04_PGRAPH_BBASE2,
	NV04_PGRAPH_BLIMIT2,
	NV04_PGRAPH_BOFFSET3,
	NV04_PGRAPH_BBASE3,
	NV04_PGRAPH_BLIMIT3,
	NV04_PGRAPH_BOFFSET4,
	NV04_PGRAPH_BBASE4,
	NV04_PGRAPH_BLIMIT4,
	NV04_PGRAPH_BOFFSET5,
	NV04_PGRAPH_BBASE5,
	NV04_PGRAPH_BLIMIT5,
	NV04_PGRAPH_BPITCH0,
	NV04_PGRAPH_BPITCH1,
	NV04_PGRAPH_BPITCH2,
	NV04_PGRAPH_BPITCH3,
	NV04_PGRAPH_BPITCH4,
	NV04_PGRAPH_SURFACE,
	NV04_PGRAPH_STATE,
	NV04_PGRAPH_BSWIZZLE2,
	NV04_PGRAPH_BSWIZZLE5,
	NV04_PGRAPH_BPIXEL,
	NV04_PGRAPH_NOTIFY,
	NV04_PGRAPH_PATT_COLOR0,
	NV04_PGRAPH_PATT_COLOR1,
	NV04_PGRAPH_PATT_COLORRAM+0x00,
	NV04_PGRAPH_PATT_COLORRAM+0x01,
	NV04_PGRAPH_PATT_COLORRAM+0x02,
	NV04_PGRAPH_PATT_COLORRAM+0x03,
	NV04_PGRAPH_PATT_COLORRAM+0x04,
	NV04_PGRAPH_PATT_COLORRAM+0x05,
	NV04_PGRAPH_PATT_COLORRAM+0x06,
	NV04_PGRAPH_PATT_COLORRAM+0x07,
	NV04_PGRAPH_PATT_COLORRAM+0x08,
	NV04_PGRAPH_PATT_COLORRAM+0x09,
	NV04_PGRAPH_PATT_COLORRAM+0x0A,
	NV04_PGRAPH_PATT_COLORRAM+0x0B,
	NV04_PGRAPH_PATT_COLORRAM+0x0C,
	NV04_PGRAPH_PATT_COLORRAM+0x0D,
	NV04_PGRAPH_PATT_COLORRAM+0x0E,
	NV04_PGRAPH_PATT_COLORRAM+0x0F,
	NV04_PGRAPH_PATT_COLORRAM+0x10,
	NV04_PGRAPH_PATT_COLORRAM+0x11,
	NV04_PGRAPH_PATT_COLORRAM+0x12,
	NV04_PGRAPH_PATT_COLORRAM+0x13,
	NV04_PGRAPH_PATT_COLORRAM+0x14,
	NV04_PGRAPH_PATT_COLORRAM+0x15,
	NV04_PGRAPH_PATT_COLORRAM+0x16,
	NV04_PGRAPH_PATT_COLORRAM+0x17,
	NV04_PGRAPH_PATT_COLORRAM+0x18,
	NV04_PGRAPH_PATT_COLORRAM+0x19,
	NV04_PGRAPH_PATT_COLORRAM+0x1A,
	NV04_PGRAPH_PATT_COLORRAM+0x1B,
	NV04_PGRAPH_PATT_COLORRAM+0x1C,
	NV04_PGRAPH_PATT_COLORRAM+0x1D,
	NV04_PGRAPH_PATT_COLORRAM+0x1E,
	NV04_PGRAPH_PATT_COLORRAM+0x1F,
	NV04_PGRAPH_PATT_COLORRAM+0x20,
	NV04_PGRAPH_PATT_COLORRAM+0x21,
	NV04_PGRAPH_PATT_COLORRAM+0x22,
	NV04_PGRAPH_PATT_COLORRAM+0x23,
	NV04_PGRAPH_PATT_COLORRAM+0x24,
	NV04_PGRAPH_PATT_COLORRAM+0x25,
	NV04_PGRAPH_PATT_COLORRAM+0x26,
	NV04_PGRAPH_PATT_COLORRAM+0x27,
	NV04_PGRAPH_PATT_COLORRAM+0x28,
	NV04_PGRAPH_PATT_COLORRAM+0x29,
	NV04_PGRAPH_PATT_COLORRAM+0x2A,
	NV04_PGRAPH_PATT_COLORRAM+0x2B,
	NV04_PGRAPH_PATT_COLORRAM+0x2C,
	NV04_PGRAPH_PATT_COLORRAM+0x2D,
	NV04_PGRAPH_PATT_COLORRAM+0x2E,
	NV04_PGRAPH_PATT_COLORRAM+0x2F,
	NV04_PGRAPH_PATT_COLORRAM+0x30,
	NV04_PGRAPH_PATT_COLORRAM+0x31,
	NV04_PGRAPH_PATT_COLORRAM+0x32,
	NV04_PGRAPH_PATT_COLORRAM+0x33,
	NV04_PGRAPH_PATT_COLORRAM+0x34,
	NV04_PGRAPH_PATT_COLORRAM+0x35,
	NV04_PGRAPH_PATT_COLORRAM+0x36,
	NV04_PGRAPH_PATT_COLORRAM+0x37,
	NV04_PGRAPH_PATT_COLORRAM+0x38,
	NV04_PGRAPH_PATT_COLORRAM+0x39,
	NV04_PGRAPH_PATT_COLORRAM+0x3A,
	NV04_PGRAPH_PATT_COLORRAM+0x3B,
	NV04_PGRAPH_PATT_COLORRAM+0x3C,
	NV04_PGRAPH_PATT_COLORRAM+0x3D,
	NV04_PGRAPH_PATT_COLORRAM+0x3E,
	NV04_PGRAPH_PATT_COLORRAM+0x3F,
	NV04_PGRAPH_PATTERN,
	0x0040080c,
	NV04_PGRAPH_PATTERN_SHAPE,
	0x00400600,
	NV04_PGRAPH_ROP3,
	NV04_PGRAPH_CHROMA,
	NV04_PGRAPH_BETA_AND,
	NV04_PGRAPH_BETA_PREMULT,
	NV04_PGRAPH_CONTROL0,
	NV04_PGRAPH_CONTROL1,
	NV04_PGRAPH_CONTROL2,
	NV04_PGRAPH_BLEND,
	NV04_PGRAPH_STORED_FMT,
	NV04_PGRAPH_SOURCE_COLOR,
	0x00400560,
	0x00400568,
	0x00400564,
	0x0040056c,
	0x00400400,
	0x00400480,
	0x00400404,
	0x00400484,
	0x00400408,
	0x00400488,
	0x0040040c,
	0x0040048c,
	0x00400410,
	0x00400490,
	0x00400414,
	0x00400494,
	0x00400418,
	0x00400498,
	0x0040041c,
	0x0040049c,
	0x00400420,
	0x004004a0,
	0x00400424,
	0x004004a4,
	0x00400428,
	0x004004a8,
	0x0040042c,
	0x004004ac,
	0x00400430,
	0x004004b0,
	0x00400434,
	0x004004b4,
	0x00400438,
	0x004004b8,
	0x0040043c,
	0x004004bc,
	0x00400440,
	0x004004c0,
	0x00400444,
	0x004004c4,
	0x00400448,
	0x004004c8,
	0x0040044c,
	0x004004cc,
	0x00400450,
	0x004004d0,
	0x00400454,
	0x004004d4,
	0x00400458,
	0x004004d8,
	0x0040045c,
	0x004004dc,
	0x00400460,
	0x004004e0,
	0x00400464,
	0x004004e4,
	0x00400468,
	0x004004e8,
	0x0040046c,
	0x004004ec,
	0x00400470,
	0x004004f0,
	0x00400474,
	0x004004f4,
	0x00400478,
	0x004004f8,
	0x0040047c,
	0x004004fc,
	0x0040053c,
	0x00400544,
	0x00400540,
	0x00400548,
	0x00400560,
	0x00400568,
	0x00400564,
	0x0040056c,
	0x00400534,
	0x00400538,
	0x00400514,
	0x00400518,
	0x0040051c,
	0x00400520,
	0x00400524,
	0x00400528,
	0x0040052c,
	0x00400530,
	0x00400d00,
	0x00400d40,
	0x00400d80,
	0x00400d04,
	0x00400d44,
	0x00400d84,
	0x00400d08,
	0x00400d48,
	0x00400d88,
	0x00400d0c,
	0x00400d4c,
	0x00400d8c,
	0x00400d10,
	0x00400d50,
	0x00400d90,
	0x00400d14,
	0x00400d54,
	0x00400d94,
	0x00400d18,
	0x00400d58,
	0x00400d98,
	0x00400d1c,
	0x00400d5c,
	0x00400d9c,
	0x00400d20,
	0x00400d60,
	0x00400da0,
	0x00400d24,
	0x00400d64,
	0x00400da4,
	0x00400d28,
	0x00400d68,
	0x00400da8,
	0x00400d2c,
	0x00400d6c,
	0x00400dac,
	0x00400d30,
	0x00400d70,
	0x00400db0,
	0x00400d34,
	0x00400d74,
	0x00400db4,
	0x00400d38,
	0x00400d78,
	0x00400db8,
	0x00400d3c,
	0x00400d7c,
	0x00400dbc,
	0x00400590,
	0x00400594,
	0x00400598,
	0x0040059c,
	0x004005a8,
	0x004005ac,
	0x004005b0,
	0x004005b4,
	0x004005c0,
	0x004005c4,
	0x004005c8,
	0x004005cc,
	0x004005d0,
	0x004005d4,
	0x004005d8,
	0x004005dc,
	0x004005e0,
	NV04_PGRAPH_PASSTHRU_0,
	NV04_PGRAPH_PASSTHRU_1,
	NV04_PGRAPH_PASSTHRU_2,
	NV04_PGRAPH_DVD_COLORFMT,
	NV04_PGRAPH_SCALED_FORMAT,
	NV04_PGRAPH_MISC24_0,
	NV04_PGRAPH_MISC24_1,
	NV04_PGRAPH_MISC24_2,
	0x00400500,
	0x00400504,
	NV04_PGRAPH_VALID1,
	NV04_PGRAPH_VALID2


};

struct graph_state {
	int nv04[sizeof(nv04_graph_ctx_regs)/sizeof(nv04_graph_ctx_regs[0])];
};

void nouveau_nv04_context_switch(struct drm_device *dev)
{
	struct drm_nouveau_private *dev_priv = dev->dev_private;
	struct nouveau_engine *engine = &dev_priv->Engine;
	struct nouveau_channel *next, *last;
	int chid;

	if (!dev) {
		DRM_DEBUG("Invalid drm_device\n");
		return;
	}
	dev_priv = dev->dev_private;
	if (!dev_priv) {
		DRM_DEBUG("Invalid drm_nouveau_private\n");
		return;
	}
	if (!dev_priv->fifos) {
		DRM_DEBUG("Invalid drm_nouveau_private->fifos\n");
		return;
	}

	chid = engine->fifo.channel_id(dev);
	next = dev_priv->fifos[chid];

	if (!next) {
		DRM_DEBUG("Invalid next channel\n");
		return;
	}

	chid = (NV_READ(NV04_PGRAPH_CTX_USER) >> 24) & (engine->fifo.channels - 1);
	last = dev_priv->fifos[chid];

	if (!last) {
		DRM_DEBUG("WARNING: Invalid last channel, switch to %x\n",
		          next->id);
	} else {
		DRM_INFO("NV: PGRAPH context switch interrupt channel %x -> %x\n",
		         last->id, next->id);
	}

/*	NV_WRITE(NV03_PFIFO_CACHES, 0x0);
	NV_WRITE(NV04_PFIFO_CACHE0_PULL0, 0x0);
	NV_WRITE(NV04_PFIFO_CACHE1_PULL0, 0x0);*/
	NV_WRITE(NV04_PGRAPH_FIFO,0x0);

	if (last)
		nv04_graph_save_context(last);

	nouveau_wait_for_idle(dev);

	NV_WRITE(NV04_PGRAPH_CTX_CONTROL, 0x10000000);
	NV_WRITE(NV04_PGRAPH_CTX_USER, (NV_READ(NV04_PGRAPH_CTX_USER) & 0xffffff) | (0x0f << 24));

	nouveau_wait_for_idle(dev);

	nv04_graph_load_context(next);

	NV_WRITE(NV04_PGRAPH_CTX_CONTROL, 0x10010100);
	NV_WRITE(NV04_PGRAPH_CTX_USER, next->id << 24);
	NV_WRITE(NV04_PGRAPH_FFINTFC_ST2, NV_READ(NV04_PGRAPH_FFINTFC_ST2)&0x000FFFFF);

/*	NV_WRITE(NV04_PGRAPH_FIFO,0x0);
	NV_WRITE(NV04_PFIFO_CACHE0_PULL0, 0x0);
	NV_WRITE(NV04_PFIFO_CACHE1_PULL0, 0x1);
	NV_WRITE(NV03_PFIFO_CACHES, 0x1);*/
	NV_WRITE(NV04_PGRAPH_FIFO,0x1);
}

int nv04_graph_create_context(struct nouveau_channel *chan) {
	struct graph_state* pgraph_ctx;
	DRM_DEBUG("nv04_graph_context_create %d\n", chan->id);

	chan->pgraph_ctx = pgraph_ctx = drm_calloc(1, sizeof(*pgraph_ctx),
					      DRM_MEM_DRIVER);

	if (pgraph_ctx == NULL)
		return -ENOMEM;

	//dev_priv->fifos[channel].pgraph_ctx_user = channel << 24;
	pgraph_ctx->nv04[0] = 0x0001ffff;
	/* is it really needed ??? */
	//dev_priv->fifos[channel].pgraph_ctx[1] = NV_READ(NV_PGRAPH_DEBUG_4);
	//dev_priv->fifos[channel].pgraph_ctx[2] = NV_READ(0x004006b0);

	return 0;
}

void nv04_graph_destroy_context(struct nouveau_channel *chan)
{
	struct graph_state* pgraph_ctx = chan->pgraph_ctx;

	drm_free(pgraph_ctx, sizeof(*pgraph_ctx), DRM_MEM_DRIVER);
	chan->pgraph_ctx = NULL;
}

int nv04_graph_load_context(struct nouveau_channel *chan)
{
	struct drm_device *dev = chan->dev;
	struct drm_nouveau_private *dev_priv = dev->dev_private;
	struct graph_state* pgraph_ctx = chan->pgraph_ctx;
	int i;

	for (i = 0; i < sizeof(nv04_graph_ctx_regs)/sizeof(nv04_graph_ctx_regs[0]); i++)
		NV_WRITE(nv04_graph_ctx_regs[i], pgraph_ctx->nv04[i]);

	return 0;
}

int nv04_graph_save_context(struct nouveau_channel *chan)
{
	struct drm_device *dev = chan->dev;
	struct drm_nouveau_private *dev_priv = dev->dev_private;
	struct graph_state* pgraph_ctx = chan->pgraph_ctx;
	int i;

	for (i = 0; i < sizeof(nv04_graph_ctx_regs)/sizeof(nv04_graph_ctx_regs[0]); i++)
		pgraph_ctx->nv04[i] = NV_READ(nv04_graph_ctx_regs[i]);

	return 0;
}

int nv04_graph_init(struct drm_device *dev) {
	struct drm_nouveau_private *dev_priv = dev->dev_private;

	NV_WRITE(NV03_PMC_ENABLE, NV_READ(NV03_PMC_ENABLE) &
			~NV_PMC_ENABLE_PGRAPH);
	NV_WRITE(NV03_PMC_ENABLE, NV_READ(NV03_PMC_ENABLE) |
			 NV_PMC_ENABLE_PGRAPH);

	/* Enable PGRAPH interrupts */
	NV_WRITE(NV03_PGRAPH_INTR, 0xFFFFFFFF);
	NV_WRITE(NV03_PGRAPH_INTR_EN, 0xFFFFFFFF);

	NV_WRITE(NV04_PGRAPH_VALID1, 0);
	NV_WRITE(NV04_PGRAPH_VALID2, 0);
	/*NV_WRITE(NV04_PGRAPH_DEBUG_0, 0x000001FF);
	NV_WRITE(NV04_PGRAPH_DEBUG_0, 0x001FFFFF);*/
	NV_WRITE(NV04_PGRAPH_DEBUG_0, 0x1231c000);
	/*1231C000 blob, 001 haiku*/
	//*V_WRITE(NV04_PGRAPH_DEBUG_1, 0xf2d91100);*/
	NV_WRITE(NV04_PGRAPH_DEBUG_1, 0x72111100);
	/*0x72111100 blob , 01 haiku*/
	/*NV_WRITE(NV04_PGRAPH_DEBUG_2, 0x11d5f870);*/
	NV_WRITE(NV04_PGRAPH_DEBUG_2, 0x11d5f071);
	/*haiku same*/

	/*NV_WRITE(NV04_PGRAPH_DEBUG_3, 0xfad4ff31);*/
	NV_WRITE(NV04_PGRAPH_DEBUG_3, 0xf0d4ff31);
	/*haiku and blob 10d4*/

	NV_WRITE(NV04_PGRAPH_STATE        , 0xFFFFFFFF);
	NV_WRITE(NV04_PGRAPH_CTX_CONTROL  , 0x10010100);
	NV_WRITE(NV04_PGRAPH_FIFO         , 0x00000001);

	/* These don't belong here, they're part of a per-channel context */
	NV_WRITE(NV04_PGRAPH_PATTERN_SHAPE, 0x00000000);
	NV_WRITE(NV04_PGRAPH_BETA_AND     , 0xFFFFFFFF);

	return 0;
}

void nv04_graph_takedown(struct drm_device *dev)
{
}
