#include "Video.h"

using namespace std;
using namespace GPL;

Video::Video() :
shader_main_basic("MainBasic"),
shader_main_texture("MainTexture"),
texture_filter{},
aspect_ratio{}
{

}

void Video::SetOrthographicZ(const float orthographic_near_z,const float orthographic_far_z)
{
	this->orthographic_near_z = orthographic_near_z;
	this->orthographic_far_z = orthographic_far_z;
}

float Video::GetOrthographicNearZ() const
{
	return this->orthographic_near_z;
}

float Video::GetOrthographicFarZ() const
{
	return this->orthographic_far_z;
}

float Video::GetPerspectiveFoV() const
{
	return this->perspective_fov;
}

const string& Video::GetShaderMainBasic() const
{
	return this->shader_main_basic;
}

const string& Video::GetShaderMainTexture() const
{
	return this->shader_main_texture;
}

void Video::SetVirtualResolution(const int virtual_width,const int virtual_height)
{
	this->virtual_resolution.SetX(virtual_width);
	this->virtual_resolution.SetY(virtual_height);
}

void Video::SetDesktopResolution(const int desktop_width,const int desktop_height)
{
	this->desktop_resolution.SetX(desktop_width);
	this->desktop_resolution.SetY(desktop_height);
}

int Video::GetVirtualWidth() const
{
	return this->virtual_resolution.GetX();
}

int Video::GetVirtualHeight() const
{
	return this->virtual_resolution.GetY();
}

void Video::SetVideoMode(const VideoMode& video_mode)
{
	this->video_mode = video_mode;
}

const VideoMode& Video::GetVideoMode() const
{
	return this->video_mode;
}

void Video::SetTextureFilter(const TextureFilter texture_filter)
{
	this->texture_filter = texture_filter;
}

TextureFilter Video::GetTextureFilter() const
{
	return this->texture_filter;
}

void Video::SetAspectRatio(const AspectRatio aspect_ratio)
{
	this->aspect_ratio = aspect_ratio;
}

AspectRatio Video::GetAspectRatio() const
{
	return this->aspect_ratio;
}

void Video::SetBackBufferClearColor(const Color& back_buffer_clear_color)
{
	this->render_target_back_buffer->SetClearColor(back_buffer_clear_color);
}

const Color& Video::GetBackBufferClearColor() const
{
	return this->render_target_back_buffer->GetClearColor();
}

unique_ptr<RenderTarget>& Video::GetPointerRenderTargetBackBuffer()
{
	return this->render_target_back_buffer;
}

const RenderTarget& Video::GetRenderTargetBackBuffer() const
{
	return *this->render_target_back_buffer.get();
}

const RenderTarget& Video::GetRenderTarget(const size_t index) const
{
	return *this->render_targets[index];
}

const RenderTarget& Video::GetLastRenderTarget() const
{
	return *this->render_targets.back();
}

const vector<const Model*>& Video::GetModelsOrthographicProjection() const
{
	return this->models_orthographic_projection;
}

const vector<const Model*>& Video::GetModelsPerspectiveProjection() const
{
	return this->models_perspective_projection;
}

vector<unique_ptr<RenderTarget>>& Video::GetRenderTargets()
{
	return this->render_targets;
}

void Video::RemoveRenderTarget(const size_t index)
{
	this->render_targets.erase(this->render_targets.begin() + index);
}

void Video::RemoveLastRenderTarget()
{
	this->render_targets.pop_back();
}

float Video::LimitBase(const float initial,const float final,const float change,const float max) const
{
	if (initial < 0)
		return change;
	else if (initial + final > max)
		return (max - final - change);
	return initial;
}

float Video::LimitX(const float x,const float w,const float change_x) const
{
	return this->LimitBase(x,w,change_x,static_cast<float>(this->GetVirtualWidth()));
}

float Video::LimitY(const float y,const float h,const float change_y) const
{
	return this->LimitBase(y,h,change_y,static_cast<float>(this->GetVirtualHeight()));
}

Rect<int> Video::AspectRatioUpdate(const RenderTarget& render_target,const Model& model) const
{
	//Aplicar o Aspect Ratio somente se o Render Target for o Back Buffer
	const bool render_target_back_buffer = (&render_target == this->render_target_back_buffer.get());

	const int width = render_target_back_buffer ? render_target.GetWidth() : this->GetVirtualWidth();
	const int height = render_target_back_buffer ? render_target.GetHeight() : this->GetVirtualHeight();

	static Rect<int> final_viewport;

	static const View* last_view{};
	static const RenderTarget* last_render_target{};
	static VideoMode last_video_mode{};

	//Evitar recalcular tudo novamente
	const bool last_view_changed = (last_view != &model.GetView());
	const bool last_render_target_changed = (last_render_target != &model.GetRenderTarget());
	const bool last_video_mode_changed = (last_video_mode != this->video_mode);
	if ((last_view_changed) || (last_render_target_changed) || (last_video_mode_changed))
	{
		if (last_view_changed)
			last_view = &model.GetView();

		if (last_render_target_changed)
			last_render_target = &model.GetRenderTarget();

		if (last_video_mode_changed)
			last_video_mode = this->video_mode;

		const Rect<float>& viewport_model = model.GetView().GetViewport();

		const Point2D<float>& viewport_model_position = viewport_model.GetPosition();
		const Point2D<float>& viewport_model_size = viewport_model.GetSize();

		if (this->aspect_ratio != AspectRatio::None)
		{
			//http://answers.unity3d.com/questions/32229/how-do-i-set-the-aspect-ratio-of-the-viewport.html

			Rect<float> viewport_scaled{0.0f,0.0f,1.0f,1.0f};

			if (render_target_back_buffer)
			{
				const float target_aspect_ratio =
					(this->aspect_ratio == AspectRatio::Normal4x3) ? (4.0f / 3.0f) :
					(this->aspect_ratio == AspectRatio::Widescreen16x9) ? (16.0f / 9.0f) :
					(this->aspect_ratio == AspectRatio::Widescreen16x10) ? (16.0f / 10.0f) : 0.0f;

				const float video_aspect_ratio = this->video_mode.GetWindowed() ?
					(static_cast<float>(this->video_mode.GetWidth()) / static_cast<float>(this->video_mode.GetHeight())) :
					(static_cast<float>(this->desktop_resolution.GetX()) / static_cast<float>(this->desktop_resolution.GetY()));

				const float scaled_height = video_aspect_ratio / target_aspect_ratio;

				//Letterbox
				if (scaled_height < 1.0f)
				{
					viewport_scaled.SetPosition(0.0f,((1.0f - scaled_height) / 2.0f));
					viewport_scaled.SetSize(1.0f,scaled_height);
				}

				//Pillarbox
				else
				{
					const float scaled_width = 1.0f / scaled_height;

					viewport_scaled.SetPosition(((1.0f - scaled_width) / 2.0f),0.0f);
					viewport_scaled.SetSize(scaled_width,1.0f);
				}
			}

			const Point2D<float>& viewport_scaled_position = viewport_scaled.GetPosition();
			const Point2D<float>& viewport_scaled_size = viewport_scaled.GetSize();

			const float scaled_distance_x = viewport_scaled_size.GetX() - viewport_scaled_position.GetX();
			const float scaled_distance_y = viewport_scaled_size.GetY() - viewport_scaled_position.GetY();

			const float scaled_x = (viewport_model_position.GetX() * scaled_distance_x) + viewport_scaled_position.GetX();
			const float scaled_y = (viewport_model_position.GetY() * scaled_distance_y) + viewport_scaled_position.GetY();

			const float scaled_width = (viewport_model_size.GetX() * viewport_scaled_size.GetX());
			const float scaled_height = (viewport_model_size.GetY() * viewport_scaled_size.GetY());


			const int viewport_x = static_cast<int>(scaled_x * width);
			const int viewport_y = static_cast<int>(scaled_y * height);
			const int viewport_width = static_cast<int>(scaled_width * width);
			const int viewport_height = static_cast<int>(scaled_height * height);

			final_viewport = {viewport_x,viewport_y,viewport_width,viewport_height};
		}
		else
		{
			const int viewport_x = static_cast<int>(viewport_model_position.GetX() * width);
			const int viewport_y = static_cast<int>(viewport_model_position.GetY() * height);
			const int viewport_width = static_cast<int>(viewport_model_size.GetX() * width);
			const int viewport_height = static_cast<int>(viewport_model_size.GetY() * height);

			final_viewport = {viewport_x,viewport_y,viewport_width,viewport_height};
		}

		if (!render_target_back_buffer)
			final_viewport.SetSize(min(final_viewport.GetSize().GetX(),render_target.GetWidth()),min(final_viewport.GetSize().GetY(),render_target.GetHeight()));
	}
	return final_viewport;
}

void Video::SortModelsPerspectiveProjection()
{
	if (!this->models_perspective_projection.empty())
	{
		vector<const Model*> models_opaque;
		vector<const Model*> models_transparent;

		for (const auto& iterator : this->models_perspective_projection)
		{
			if (iterator->IsOpaque())
				models_opaque.push_back(iterator);
			else
				models_transparent.push_back(iterator);
		}

		static const auto sort_z_near_to_far = [](const Model* model_a,const Model* model_b) -> bool { return (model_a->GetZPriority() < model_b->GetZPriority()); };
		sort(models_opaque.begin(),models_opaque.end(),sort_z_near_to_far);

		static const auto sort_z_far_to_near = [](const Model* model_a,const Model* model_b) -> bool { return (model_a->GetZPriority() > model_b->GetZPriority()); };
		sort(models_transparent.begin(),models_transparent.end(),sort_z_far_to_near);

		this->models_perspective_projection.clear();
		for (const auto& iterator : models_opaque)
			this->models_perspective_projection.push_back(iterator);

		for (const auto& iterator : models_transparent)
			this->models_perspective_projection.push_back(iterator);
	}
}

void Video::Draw(Model& model)
{
	//Se o Model não tiver nenhum Render Target então utilizar o Back Buffer para o Model
	if (!&model.GetRenderTarget())
		model.SetRenderTarget(*this->render_target_back_buffer);

	//Se o Model não tiver nenhum View então utilizar o View padrão para o Model
	if (!&model.GetView())
		model.SetView(this->view);

	//Se tiver algum Vertex para ser renderizado posteriormente
	if (model.GetVertexTotal())
	{
		vector<const Model*>* models_target{};

		if (model.GetProjection() == Projection::Orthographic)
			models_target = &this->models_orthographic_projection;

		else if (model.GetProjection() == Projection::Perspective)
			models_target = &this->models_perspective_projection;

		models_target->push_back(&model);
		model.SetSourceModelAdded(*models_target);
	}
}

void Video::ClearModels()
{
	this->models_orthographic_projection.clear();
	this->models_perspective_projection.clear();
}